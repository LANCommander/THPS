# THPS1 Decompilation — Phase 1 Coverage & Scoping Report

*Generated 2026-09-28. Numbers come from the tools in `tools/` run against the extracted
binaries; regenerate with `tools/parse_psyq_sym.py` and `tools/match_functions.py`.*

## TL;DR

- The Euro-demo disc yields an **early THPS2 build (`PROSKATE.EXE`) with a full Psy-Q debug
  `.SYM`**: **1,645 functions, all typed, across 98 source files, plus 156,874 C type
  definitions and complete source-line info.** This is a near-complete map of the Neversoft
  engine that THPS1 also runs.
- Retail **THPS1 (`SLUS_008.60`) has no symbols**, but shares that engine. A conservative
  instruction-shape match finds **474 demo functions (31.7%) byte-for-byte in retail THPS1**
  (a hard lower bound), concentrated in the low-level engine/math/IO modules.
- Net: we do **not** start from zero. In Ghidra, retail THPS1 has **1,758 functions**, of which
  **920 (52%) are already named** — 474 ported from the demo by exact match + 446 Psy-Q library
  functions the loader fingerprinted (incl. 153 GTE macros). That leaves **838 unnamed game
  functions** as the real decompilation surface, and the demo supplies names/types/source-file
  structure to attack them.
- **Recommended first milestone:** bring up the **symbol-rich THPS2 demo** (100% of its own
  functions are named/typed) to prove the toolchain, then retarget onto retail THPS1.

---

## 1. Binary inventory

| Item | Boot / file | Text base | Text size | Symbols |
|---|---|---|---|---|
| **THPS2 demo** (early, "sk2demo") | `PROSKATE.EXE` (menu boots `SCED_026.60`) | `0x80018000` | 0xD7000 (880,640) | **full Psy-Q `MAIN.SYM`** |
| **THPS1 retail** (port target) | `SLUS_008.60` | `0x80010000` | 0xCD000 (839,680) | none |
| THPS2 retail (reference) | (`Tony Hawk's Pro Skater 2 (USA).chd`) | — | — | none |

Both are US-region PSX-EXEs. The demo is on a multi-game Euro demo disc; its THPS content lives
under `PROSKATE/` (`MAIN.SYM`, `CD.WAD`, streams). Extraction: `chdman extractcd` (retail CHDs) →
`dumpsxiso` (see `tools/` recipes and `extern/*/*.xml`).

The demo build predates the *engine* in retail THPS1 in some subsystems and postdates it in others
(THPS1 shipped 1999-09; this THPS2 demo is ~mid-2000). Treat the demo as the **same engine, a
later branch** — identical low-level code, reworked game logic.

## 2. Demo symbol census (`MAIN.SYM`, 4.5 MB)

- **Debug richness: FULL** — function boundaries, C types, and source/line data all present.
- **1,645 functions** (every one sized), totalling **556,068 bytes of game code** (~63% of the
  demo's text; the other ~37% is un-symboled Psy-Q library + data).
- **3,641 addressed symbols**, **156,874 C type definitions** (50,597 struct members, plus ints,
  enums, unions…), **49,780 source-line records**, **98 source files**.

### Engine module map (top source files by function count)

| module | funcs | KB | role |
|---|---:|---:|---|
| PHYSICS.CPP | 99 | 64.4 | skater physics (`CBruce`), trick state |
| BIT.CPP / BIT2.CPP | 117 | 31.5 | core bit/asset/streaming primitives |
| CREATE*.CPP | 89 | 25.7 | create-a-skater / park pieces |
| PHYSICS + M3D*.CPP | — | — | 3D transform, `M3DCOLIJ` collision |
| FRONT/MENU/PANEL/RFRONT | 170 | 60+ | front-end & HUD |
| LEVELEDITOR/LEVELGEN/EDITORPIECES | 80 | 35 | park editor |
| CAMERA.CPP | 35 | 21.0 | camera |
| TRIG/VECTOR/QUAT.CPP | 70 | 17.3 | math |
| SPOOL/SPOOLER/REDBOOK | 62 | 12.7 | CD streaming + Red Book audio |
| CARD.CPP | 19 | 4.0 | memory card |
| PAD.CPP | 15 | 4.4 | controller |
| SFX/VIDEO/IMAGE/PAL/FONT* | — | — | audio + GPU/TIM presentation |
| RAIL/TRICKOB/TRICKTIPS | 29 | 9.9 | grinding & tricks |

(Full table: `build/MAIN_sym.json` / rerun `tools/parse_psyq_sym.py`.)

## 3. Demo → retail-THPS1 correlation (spot-check)

Method: normalise each demo function's MIPS (mask j/jal targets and lui/addiu/ori/load/store
immediates — the fields that move under a different link base), then search the whole retail
`.text` for the exact normalised sequence. An exact hit means the same function, unchanged since
THPS1. This is a **strict lower bound** (THPS1 is older; evolved functions won't match exactly).

- **474 / 1,494 sized demo functions match exactly (31.7%)** — 18.2% of code bytes.
- A fuzzy (≥90% instruction) pass over a sample added only ~2.5%, i.e. functions that are *not*
  exact are genuinely rewritten between the two builds, not merely relocated.

### Where the overlap is (exact match rate by module)

| high overlap (stable engine) | rate | low overlap | rate |
|---|---:|---|---:|
| VECTOR | 100% | LEVELEDITOR / LEVELGEN | 0% |
| UTILS | 91% | EDITORPIECES | 0% |
| M3DUTILS | 88% | CREATE | 4% |
| CARD | 83% | GENOBJS / IMAGE / RAIL | 0% |
| VIDEO | 81% | DUST / FONTTOOLS | 0% |
| PACK | 79% | LEVELSELECT2 | 3% |
| PAD | 73% | MENU | 9% |
| MESS | 72% | PHYSICS | 15% |
| TRIG / FRONT | 67% | POWERUP / CAMERA | ~36% |
| SPOOL / OB / SHELLUTILS | ~52% | | |

**Reading:** the *engine substrate* THPS1 shares with the demo — math, memory-card, controller,
CD streaming, video/image, generic object plumbing — is largely identical, so the demo symbols
name it directly.

The near-zero modules split into two very different cases:

- **THPS2-only features that DON'T EXIST in THPS1 — out of scope, not work.** THPS1 had no
  create-a-skater (`CREATE.CPP`, `CREATE_TEX.CPP`, `CREATE_COLOR.CPP`) and no create-a-park / level
  editor (`LEVELEDITOR.CPP`, `LEVELGEN.CPP`, `EDITORPIECES.CPP`). These ~170 demo functions have no
  THPS1 counterpart at all — their 0–4% match is *correct*, and they should be excluded from any
  THPS1 decomp/port scope.
- **Genuinely evolved engine code.** `PHYSICS.CPP` matches only 15% largely because THPS2 added
  **rolling manuals and the balance meter** (in the `CBruce` skater/trick code) — mechanics THPS1
  does not have. So THPS1's physics is a *simpler ancestor* of the demo's: the demo names/types
  guide it, but THPS1's versions are smaller and must be decompiled from the retail binary.

So the demo *over-represents* THPS1: subtract the create-a-skater/park modules and the
manual/balance additions, and what remains is a clean superset of the THPS1 engine.

The 474 exact matches are already emitted as retail-address labels in `build/retail_names.tsv`
and can be applied to the retail program in Ghidra (`ghidra_scripts/ApplyPsxSym.java`).

## 4. What this means for effort (both end-goal paths)

Exact counts from the Ghidra import (both programs are in `ghidra/THPS.gpr`):

| program | total funcs | named | unnamed `FUN_*` |
|---|---:|---:|---:|
| THPS2 demo (`PROSKATE.EXE`) | 2,355 | 1,645 game (from `MAIN.SYM`) + ~710 Psy-Q lib | ~0 |
| **THPS1 retail (`SLUS_008.60`)** | **1,758** | **920** (474 demo-ported + 446 Psy-Q lib) | **838** |

So the retail decompilation surface is **~838 game functions**. The demo is larger/newer precisely
because THPS2 *added* features THPS1 lacks — create-a-skater, create-a-park/level editor, rolling
manuals and the balance meter. THPS1 has none of these, so the 838 retail functions are a **smaller,
simpler set** than the demo's 1,645: no editor/create modules at all, and a leaner `CBruce` physics
without manual/balance logic. Every retail function still has a demo counterpart or ancestor to
reference for names and types (the demo is a superset of the THPS1 engine).

### Path A — Matching decompilation to C (readable source)
- **Leverage:** the demo `.SYM` hands us names, prototypes, struct layouts and source-file
  grouping for the entire engine — normally the most expensive part of a scratch decomp. ~1/3 of
  retail is already identified; the rest is same-module, evolved.
- **Cost:** still large — every retail function must be written in C and matched to the original
  MIPS (Psy-Q/GCC recompile + objdiff). Order **~1,500 functions**; a multi-person-month to
  multi-person-year effort depending on match strictness. Produces the most faithful, reusable
  result and a true source port.
- **Toolchain to add later:** Psy-Q (or modern GCC-mipsel) recompile, `splat`/`spimdisasm`,
  `asm-differ`/`objdiff`, `decomp.me` scratches, `maspsx`.

### Path B — Static recompilation (RecompOne, fastest to playable)
- **Leverage:** symbols aren't required, but the demo's types make the generated code debuggable
  and the HLE boundary obvious (CD/SPU/GPU/GTE/pad calls are all named in the demo).
- **Cost:** stand up RecompOne (MIPS→C#, .NET 10) on the retail PSX-EXE, then implement/verify the
  HLE runtime (GPU, SPU, CD-ROM, GTE, controllers, memory card) until it boots and plays. Much
  faster to a *playable* build; output is generated C#, not readable source. RecompOne is early
  and its maintainers decline AI-authored contributions (use, don't upstream).

### Decision — HYBRID (chosen 2026-09-28)

**Static recompilation is the base; hand-decompilation is an incremental overlay.** These paths are
not a fork — RecompOne's design makes them one architecture:

- **Game logic → statically recompiled, untouched.** All ~838 THPS1 game functions are lifted
  MIPS→C# and run as-is. *Zero* game-logic decompilation is required to reach playable.
- **Hardware/platform layer → native, not lifted.** The Psy-Q library calls (`libgpu`, `libspu`,
  `libcd`, `libpad`, `libcard`, `libgte`, `libetc`) are **reimplemented natively** by RecompOne's
  runtime (it applied 48 reimplementations to THPS1). "Functions needed for the port" = this HLE
  boundary, and it is *reimplemented*, not decompiled from the game.
- **Selective native decomp → optional, incremental, later.** Every call routes through
  `Dispatcher.Call(c, m, addr)`, and `HookManager.AddReplace(target, impl)` overrides any single
  function with a native version — the same one-function-at-a-time, A/B-verifiable model Hydro
  Thunder used with `HY_PORT`, here over the lifted C# instead of an in-process binary.

So Path B (recomp) reaches playable fastest with no game decomp, and Path A (the matching toolchain
in `decomp/`) becomes a **quality/verification and eventual-readable-source overlay**, not a gate on
playability. For native C# overrides, byte-exact matching isn't even required — behaviourally
equivalent + A/B-verified against the lifted function suffices, which is far cheaper per function.

## 5. Confidence & caveats

- The 31.7% figure is a **floor**, not the shared-code total: it counts only byte-identical
  functions. The true "engine THPS1 shares with the demo" is larger but evolved. Verified live:
  the ported `GetFaceFlags__FP9SLineInfo` decompiles identically in both binaries over MCP.
- Retail counts are the analyzer's exact numbers (1,758 total / 920 named / 838 `FUN_*`).
- `dumpsxiso` flagged the demo's CDDA as out-of-bounds (audio is Track 2) — irrelevant to code.

## 6. Phase 2 — hybrid, playable-first (in progress)

Spike results and the running port are in **`docs/phase2-spike.md`**. Status: RecompOne lifts all of
THPS1 to C# (1,663 functions), the host compiles, and the port **boots and RENDERS THE THPS1 TITLE
SCREEN on Windows** (`build/thps_t110.png`) — past `WaitForValidDisc`, through the intro (FMVs
skipped via injected Start+Cross), loading `CD.WAD` and drawing the title via the normal GPU path.

Known gap: MDEC-decoded **FMV frames don't display** (intro movies are black) — a RecompOne
MDEC-present/`.STR` HLE issue, likely upstream; it does not block the title/menus. Remaining toward
interactive gameplay: input wiring, closing FMV/HLE gaps, and — as the overlay — applying the demo's
**types** in Ghidra and replacing selected lifted functions with native C# via
`HookManager.AddReplace` (A/B-verified), prioritising shared-engine modules.
