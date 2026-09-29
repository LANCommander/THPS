# Phase 2 spike — decompilation vs. static recompilation

Goal: measure the two production paths on THPS1 to pick one. Vertical-slice module chosen for the
matching-decomp arm: **VECTOR.CPP** (28 functions, 100% exact demo↔retail match, pure math, no HLE).

## Arm B — Static recompilation (RecompOne) — **executed, very promising**

Environment: .NET SDK 10 present. RecompOne cloned to `tools/vendor/RecompOne` (git-ignored) and
built clean.

Pipeline run against retail THPS1 (`build/thps1.cue`):
1. `--autoconfigure` — signature DB (2,949 funcs / 9,674 variants) found **1,660 functions**, named
   186 Psy-Q library funcs (libgte/libgpu/libcd/libspu/libpad/libcard/…). Corroborates Ghidra's
   1,758. Wrote `build/recompone_thps1/THPS1.json`.
2. Recompile — emitted **1,663 functions → `build/generated/main.cs` (194,390 lines, 20 MB)** plus
   an auto-generated `Entry.cs` boot sequence (load `SLUS_008.60` → BIOS init → call `0x80091F9C`)
   and `Stubs.cs`. 48 library reimplementations applied.
3. Host — a ~6-line host (`build/recompone_port/`) referencing `RecompOne.Runtime` **compiles clean
   (0 errors)** to a native .NET exe.
4. Run — launches, opens a window, brings up **OpenGL 4.5 GPU backend + audio, no crash**.
5. **Boot (2026-09-28):** `WaitForValidDisc` reads `ConfigManager.Game.CdPath`; seeding it via a
   `settings.json` (host writes it in `build/recompone_port/Program.cs`) clears the gate. The port
   then **executes the game entry point `0x80091F9C` and runs THPS1's own code** — logging
   `ResetGraph:jtb=800c94a8,env=800c94f0` (the game's first `libgpu` call) and staying alive. The
   window and host UI render; the **game viewport is still black** (no game frame yet).

**Result:** whole-binary lift + compile + boot-to-executing-game-code. Throughput is essentially
"the whole game at once."

### Boot diagnosis (2026-09-28) — reaches the intro, stalls on `.STR` streaming

With the runtime trace toggles (`RecompOne.Runtime.Log.*`, wired to `THPS_TRACE=1` in the host) the
boot is fully characterised:
- Reads `CD.HED`, indexes every disc file (all `.STR`, `CD.WAD`, `INTRO.STR`), sets up CD streaming
  (`StSetStream`/`StSetRing`) and enters the main loop (`VSync` every frame). No errors.
- **MDEC works:** ~274 `[MDEC] decode` calls, each 300 macroblocks / 57,600 words (a 320×240 16-bit
  frame) — the Activision logo FMV is decoding.
- **But:** the CD stream position climbs 00:00:00 → 08:35:27 and then **stalls at 08:35:27** (LBA
  ~38502, inside `ATVILOGO.STR`). `StGetNext` never appears in the trace (only `StSetStream`/
  `StFreeRing`), and there are **zero `[GPU]` primitive calls** — the decoded frames are never
  presented. Window + host UI render; the game viewport stays **black** (verified via `PrintWindow`).

### FIRST RENDER (2026-09-28) — the THPS1 title screen renders on Windows

Injecting Start+Cross directly into `RecompOne.Runtime.Hardware.Controller.State` from a host thread
(`THPS_SKIP=1`, out-racing `InputManager`; tapping so each press is a fresh edge) skips the logo
FMVs — confirmed by the CD stream advancing `ATVILOGO.STR (08:35)` → `LOGO.STR (35:05)` →
`INTRO.STR (31:46)`. The intro plays out, then the game **reads `CD.WAD` (low LBAs) for the
front-end and renders the Tony Hawk's Pro Skater TITLE SCREEN** (`build/thps_t110.png`). The
mainline GPU/asset render path works.

**One known gap remains:** MDEC-decoded **FMV frames don't display** (every intro movie is black —
MDEC decodes ~57,600 words/frame but the decode→VRAM→present path yields no output). That's a
`RecompOne.Runtime` MDEC-present / `.STR` streaming issue, likely upstream. It does **not** block the
game — the title and menus render via normal GPU primitives. So the port **boots, runs, and renders
THPS1 on Windows**; polishing FMV playback and closing HLE gaps toward interactive gameplay is the
ongoing work.

### Menu → gameplay — blocked by a front-end recomp crash (2026-09-28)

Getting past the title into the menus deterministically **crashes**. A single Start tap at the
title (after the intro; the injector is delayed so it never presses during init) triggers the
title→menu transition, which throws:

```
System.InvalidOperationException: unmapped call: 0x00C00D52
  at func_80043AF4  (called by func_80043B50 = CBody::UpdateShadow)
  ... func_80026D44 <- entry 0x80091F9C
```

`func_80043AF4` performs a **virtual/vtable dispatch** — `obj=S0`, `sub=*(obj+0xD0)`,
`type=*(sub+0x44)`, `fn=*(type+0xC)`, `call fn` — and `fn` reads back garbage (`0x00C00D52`),
i.e. an object's vtable/type pointer is wrong/uninitialised (the game also logs
"No PREMgr to delete"). So the game's per-frame 3D **shadow update** (`CBody::UpdateShadow`) hits a
bad polymorphic call the moment the menu's skater model updates. It is a genuine RecompOne
recomp-correctness gap in the front-end, not an input artifact (deterministic on one clean tap).

**Update — it is INHERENT, not input-driven, and cascading (investigated 2026-09-28):**
- With input delayed so Start is pressed *zero* times, the game still crashes at the same
  `0x00C00D52` on its own — the crash is in THPS's **automatic attract / scene-transition flow**,
  not triggered by navigation. (Earlier "title renders" runs were killed before the auto-transition.)
- The crashing callee `func_80043AF4` is called **directly** (compiled as a C# method call), so a
  `Dispatcher._funcMap` override does not intercept it — a real override needs a MonoMod detour of
  the generated method (`HookManager.AddReplace`).
- `Dispatcher.Tolerant = true` (skip unmapped indirect calls) *does* skip `0x00C00D52`, but the game
  then crashes **downstream** with `unmapped address: 0xFFFFFF54` (a null/garbage memory access). So
  the root cause is deeper than one call: **front-end scene objects are left uninitialised** (the
  shadow's type/vtable is garbage; the `PREManager` global `PREMgr` @ demo `0x800e2b8c`, created by
  `PRE_Init` in PRE.CPP, is null — hence "No PREMgr to delete").

**Conclusion:** reaching gameplay is blocked by a **cascading front-end recomp-correctness gap** in
RecompOne's lift of THPS's scene/attract initialisation — not something a single per-function native
override fixes (the whole init path must be made correct). This is deep recomp-internals work and
likely an **upstream RecompOne** issue. Candidate directions: (a) find why the scene-init /
`PRE_Init` / C++ static-ctor setup doesn't run correctly in the lift; (b) MonoMod-detour a cluster
of front-end functions to native C# (using the demo's PRE.CPP/OB.CPP types) — a much larger overlay
than one function; or (c) report it upstream and revisit. The static title screen still renders, and
the recomp is correct enough to boot, stream, decode, and run the main loop — the gap is specifically
the interactive front-end init.

Experimental toggles left in the host: `THPS_TOLERANT=1` (skip unmapped calls) and `THPS_OVERRIDE=1`
(the inert `_funcMap` example). Neither is on by default.

Tooling note: the game window renders only in the interactive (foreground) session; background
PowerShell can't enumerate/capture it, and long (>120 s) foreground runs hit the tool timeout — so
menu iteration is currently awkward to automate. Making the port able to **skip the intro fast**
(it's ~100 s of black FMV) would greatly speed up front-end iteration.

### Keyboard input — verified working (2026-09-28)

Real keyboard input flows `key → Silk.NET IsKeyPressed → InputManager → Controller.State → game`
(`RecompOne.Runtime/Host/InputManager.cs`, polled every frame). Confirmed end-to-end: with the THPS
window focused, real Enter/Z keystrokes advanced the intro stream (`08:35 → 35:05`), i.e. the game
skipped a logo on real input. All default key names parse to valid `Silk.NET.Input.Key` values
(a startup check was used to confirm). Default bindings: D-pad = arrows, Cross = Z, Circle = X,
Square = A, Triangle = S, Start = Enter, Select = Right Shift, L1/R1 = Q/W, L2/R2 = E/R, L3/R3 = F/G
(rebindable in the in-window Settings). The host (`build/recompone_port/Program.cs`) uses real input
by default; `THPS_SKIP=1` (dev only) auto-taps Start+Cross to blow past the black FMVs, and
`THPS_TRACE=1` enables the HLE trace.

Caveats: output is generated C# (not readable source); ties the port to RecompOne's runtime;
RecompOne is early-stage and its maintainers decline AI-authored PRs (use, don't upstream).

## Decision — HYBRID (playable-first via recomp, decomp as overlay)

The two arms are one architecture, not a fork (full rationale in `coverage-report.md` §4 "Decision"):
game logic stays **statically recompiled and untouched**; the hardware/platform layer is **native**
(RecompOne runtime HLE, already largely provided); and any single function can later be replaced with
a hand-written native version via `HookManager.AddReplace` (dispatch seam), A/B-verified — no
game-logic decompilation is required to reach playable. The `decomp/` toolchain becomes a
quality/verification + eventual-readable-source overlay, not a gate.

## Arm A — Matching decompilation to C — **toolchain stood up (now the overlay path)**

Per the hybrid decision this is no longer the gate to playable — it's the quality/verification and
eventual-readable-source overlay. Toolchain runs natively on Windows via Node (no Docker/WSL).
Working harness in `decomp/` (see `decomp/README.md`):
- **Compiler up:** `psyq-wasm` (PsyQ 4.4 `cc1psx` / GCC 2.8.1, byte-exact) + `tools/compile.mjs`
  and `tools/diff.mjs`. Verified: compiles C to exact PsyQ MIPS assembly.
- **Assembler up:** `psyq-asm` (ASPSX 2.77/2.81-compatible) assembles cc1psx output to R3000 words
  and inserts delay-slot/hazard nops. `tools/match.mjs` runs the whole pipeline and diffs the
  produced words against the real bytes in `SLUS_008.60`. **Full toolchain stood up, all in Node.**
- **First function — `CVector::operator+=` (`0x8004da3c`):** prologue (`move v0,a0`) + first load are
  byte-exact and nops are inserted correctly; remaining diff is register allocation + load
  scheduling, i.e. a **compiler-version** artifact (psyq-wasm is GCC 2.8.1 / PsyQ 4.4; THPS1 likely
  GCC 2.7.2 / PsyQ 4.0). Next: swap in a 2.7.2 `cc1psx` and iterate — normal decomp work, harness
  unchanged. (Could move to `objdiff` later once emitting ELF objects.)

Once up, the VECTOR slice is ideal: `CVector::Length/Normalize/operator+=/…` are small, pure, and
100%-matching between demo and retail, and the demo `.SYM` supplies exact prototypes and the
`CVector`/`SVECTOR` types. Expected throughput: a handful of functions/day early, rising with
infra — a multi-month effort for the ~838 unnamed retail game functions, yielding readable,
faithful source.

## Recommendation (to revisit with the user)

- If the priority is **playable soon**: continue Arm B — get past `WaitForValidDisc`, then iterate
  HLE until THPS1's intro/menu renders. Highest momentum; RecompOne already does the heavy lifting.
- If the priority is a **faithful, readable, maintainable source port**: invest in Arm A's toolchain
  and decompile module-by-module, using the demo symbols/types throughout.
- Hybrid worth considering: ship Arm B as the playable target while decompiling hot modules to C for
  correctness/mods over time.

Next concrete step either way: (B) author the disc handshake / point the host at the cue and debug
first frame; or (A) stand up the mipsel-gcc + maspsx + objdiff toolchain and match the first VECTOR
function.
