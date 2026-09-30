# THPS1 decompilation priorities — by call frequency × viability

Generated from `tools/callcount.py` (direct-JAL call counts over retail `SLUS_008.60`) plus
Ghidra decompilation to classify each target. Rationale: decompile the **most-called** functions
first — each one fixed/ported affects the most call sites.

Retail `.text`: **2,377 distinct call targets, 8,051 direct calls, 335 indirect (jalr).**
401 of the call targets are demo-exact-named; of the **top 100 most-called, 44 are demo-named game
functions**, the rest unnamed (Psy-Q library or unmatched game code).

## Viability classes
- **✅ viable, easy** — small game utility/math/setter, no division/GTE. Do first.
- **🟡 viable, medium** — larger or touches allocators/state; still game code.
- **🔴 harder** — big/complex (text layout, collision).
- **⛔ skip** — Psy-Q **library** (the runtime/HLE provides these; never decompile).

## Top targets (ranked by calls)

| calls | addr | function | class | notes |
|---:|---|---|---|---|
| 200 | 0x8004b250 | *(unnamed)* angle/table lookup | 🟡 | clamps to 0x4000; fixed-point trig-like |
| 190 | 0x8001e114 | *(unnamed)* text/string draw | 🔴 | many locals, char* — layout code |
| 133 | 0x8004794c | `Rnd__Fi` (UTILS) | ✅ | RNG, 92B — high value, easy |
| 109 | 0x8008b900 | `sprintf` | ⛔ | Psy-Q library |
| 102 | 0x800241dc | `CItem::operator new` (OB) | 🟡 | pool allocator |
| 89 | 0x8001d2d0 | `Mess_SetRGB` (MESS) | ✅ | 60B setter |
| 86 | 0x80070a60 | `Pad_ClearTriggers` (PAD) | ✅ | 32B — trivial |
| 86 | 0x8004d5d0 | *(unnamed)* pool free | 🟡 | game allocator (DAT_800d1b48) |
| 84 | 0x8004d068 | *(unnamed)* pool alloc | 🟡 | game allocator (DAT_800d1b40) |
| 76 | 0x8001d250 | *(unnamed)* 1-line setter | ✅ | `DAT_800d15f0 = arg` — trivial |
| 73 | 0x8001d25c | `Mess_SetScale` (MESS) | ✅ | 52B setter |
| 72 | 0x8004dcfc | `operator-(CVector,CVector)` | ✔ done | already byte-matched |
| 69 | 0x80063be4 | `Sprite::draw` (SHELLUTILS) | ✅ | 100B |
| 63 | 0x800720ec | *(unnamed)* **vec dot product** | ✅ | `Σpᵢ·qᵢ >>12` — small pure math, ideal |
| 46 | 0x8001692c | `CMenu::ChoiceIs` (FRONT) | ✅ | 64B |
| 46 | 0x8004de8c | `operator>>(CVector,int)` | ✔ done | already byte-matched |
| 40 | 0x8001f144 | `Mess_SetCurrentFont` | ✅ | 112B |
| 35 | 0x800167f0 | `CMenu::AddEntry` (FRONT) | ✅ | 136B |
| 35 | 0x80047600 | `Trig_GetPosition` (TRIG) | 🟡 | 372B |
| 32 | 0x80068b34 | `PutNBits` (VIDEO) | ✅ | 196B bit-packer |
| 30 | 0x8004da3c | `operator+=` | ✔ done | already byte-matched |
| 27 | 0x8007eb08 | `M3dColij_InitLineInfo` | 🔴 | 892B collision |

(Full list: `python tools/callcount.py 200`.)

## Verdict — are they viable? Mostly YES.
The high-use functions are overwhelmingly **viable game code**: small utilities (`Rnd`, the MESS/PAD
setters, the 1-line setters), pure math (the dot product, and the VECTOR ops already matched), and
game allocators. The only categories to avoid are **Psy-Q library** functions (e.g. `sprintf` —
provided by the runtime, never decompiled).

## Viability nuances (discovered while matching)
- **Pure register / pointer / stack functions match now** with `matchcc.mjs` (all 14 VECTOR ops
  did). No project infrastructure needed.
- **Functions that reference globals/statics need the linker/splat setup first.** e.g. the
  high-call setters (`FUN_8001d250` = `DAT_800d15f0 = arg`, the `Mess_Set*` globals) emit
  `lui/sw` against absolute addresses; those bytes only match once each global is placed at its
  real address (a `splat`-style memory map + linker script). So the *simplest* functions by logic
  are **not** the first to byte-match — do the self-contained math/util ones first, then stand up
  the project layout for the global-referencing majority.
- **Complex fixed-point (64-bit MAC, e.g. the dot product) is viable but needs C-structure
  iteration** — the register allocation/scheduling of `mult`/`mflo`/`mfhi` accumulation is
  sensitive to how the C is written (temps, accumulation order). Reached 6/30 on a first attempt.
- **Division & GTE are unblocked:** `match_div.py` handles bare div, GTE (SDK headers + DMPSX)
  and relocations together (see `decomp/README.md`). `Length`, `Normalize` and
  `M3dUtils_NormaliseVector` all matched on the first draft.

## Recommended order
1. **Trivial/high-call setters & utilities:** `FUN_8001d250`, `Pad_ClearTriggers`, `Mess_SetRGB`,
   `Mess_SetScale`, `Mess_SetCurrentFont`, `Mess_SetFontScale` — fast wins, huge call coverage.
2. **`Rnd__Fi`** (133 calls) — the single highest-value named game function.
3. **The vector dot product** `FUN_800720ec` (63) and remaining pure-math VECTOR/CSVector ops.
4. **CItem pool allocator** cluster (`operator new`, `FUN_8004d068`, `FUN_8004d5d0`) — unlocks a lot
   of object code; medium effort.
5. **Menu/UI** (`ChoiceIs`, `AddEntry`, `Sprite::draw`) and **TRIG** helpers.
6. Defer: the big text-layout (`FUN_8001e114`) and collision (`M3dColij_*`). Division/GTE functions
   are no longer blocked.
