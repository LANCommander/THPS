# THPS1 matching-decompilation harness

Matching-decomp arm of the project (the readable-C path). Toolchain runs natively on Windows via
Node — no Docker/WSL/Psy-Q-binary needed.

## What works now — full pipeline, all in Node (no Docker/WSL/binaries)

`C source → cc1psx (psyq-wasm) → ASPSX (psyq-asm) → R3000 words → diff vs SLUS_008.60`

- **Compiler:** `psyq-wasm` = PsyQ 4.4 `cc1psx` (GCC 2.8.1), byte-exact vs the real compiler.
- **Assembler:** `psyq-asm` = ASPSX 2.77/2.81-compatible encoder; expands macros and **inserts
  delay-slot / hazard nops** like Sony's assembler.
- **`tools/compile.mjs <src.c> [-O2] [-G0|-G8] [-o out.s]`** — C → PsyQ assembly.
- **`tools/diff.mjs <src.c> <expected.txt>`** — instruction-level diff vs a Ghidra listing.
- **`tools/match.mjs <src.c> <retailAddrHex> <sizeBytes> [-G0|-G8]`** — the real deal: compile +
  assemble + compare machine words against the function's actual bytes in `SLUS_008.60`.

Validated on `CVector::operator+=` (`0x8004da3c`): the `move v0,a0` prologue and first load are
**byte-exact**, and psyq-asm inserts the correct delay-slot nops. The pipeline is complete.

## First target: `CVector::operator+=` (retail `0x8004da3c`) — 3/15 words, diagnosis clear

`src/vector.c` + `expected/CVector_apl.txt`. Run: `node tools/match.mjs src/vector.c 0x8004da3c 60 -G8`.
- Returning `*this` (operator+= returns a reference) made the `move v0,a0` prologue + first load
  byte-exact.
- Remaining diff = register allocation (`a2` vs `a0`) + software-pipelined load scheduling. Both are
  **compiler-version** artifacts: `psyq-wasm` is GCC 2.8.1 (PsyQ 4.4); the target schedules like
  **GCC 2.7.2 (PsyQ 4.0)**, standard for Aug-1999 titles.

## Global-referencing functions — UNLOCKED (linker-lite reloc resolution)

**THPS1 is `-G8`** (not -G0): small globals are addressed **gp-relative**, `gp = 0x800d1080`
(derived from `sb a0,1392(gp)` → `0x800d15f0`). Functions with no globals match with `-G0`/`-G8`
either way; global-referencing functions need the gp layout.

`tools/match_sym.mjs <src.c> <addr> <size> <syms.json> [-O2]` handles them: reference a global by
name in the C (**define** it, e.g. `unsigned DAT_800d15f4;`, so cc1 emits a **GPREL16**/HI16/LO16
relocation), give its address in `syms.json` (`{"gp":"0x800d1080","DAT_800d15f4":"0x800d15f4",…}`),
and the tool resolves the relocations (gprel = `sym-gp`, hi/lo = split addr) before byte-diffing —
no full linker needed. Verified: `sb a0,1392(gp)` resolves exactly. Global addresses come from the
retail Ghidra `DAT_########` labels.

`match_sym.mjs` resolves **GPREL16** (small globals), **HI16/LO16** (large data), and **MIPS26**
(function calls *and* local control-flow jumps — the latter via the function's own base address).
Symbol addresses come from retail Ghidra `DAT_########` / `FUN_########` labels.

## 29 functions byte-exact (running total)

- **VECTOR / CVector (17):** all 14 operators above + `operator/=`, `operator/(V,int)` (via
  `match_div.py`), and `KillSmall`.
- **CSVector (4):** `operator+=`, `operator/=` (div), `Mask`, `KillSmall`.
- **PAD (4):** `Pad_ClearTriggers`, `Pad_LockAnalog`, `Pad_ClearAll`, `Pad_Clear`.
- **M3DUTILS (1):** `M3dUtils_AnglesFromMatrix` (172B, 4 calls incl. `ratan2` — 43/43 first try).
- **MESS/SFX/UTILS (3):** `FUN_8001d250` setter, `Mess_SetRGB`, `SFX_Stop`.

Observation: **structured functions with calls/control-flow tend to match on the first try** (call
sequence constrains ordering) — `AnglesFromMatrix` did. The fiddly cases are small register-shuffle
functions (regalloc freedom) and struct-array field offsets (`ReadHooksPacket` needs
`struct S array[]; array[i].field`).

## Next infrastructure — GTE (`libgte.h`)
GTE functions (`Length`, `Normalize`, `NormaliseVector`, much of M3D/physics) use `gte_*` **inline
macros** that expand to `cop2`/`lwc2`/`swc2`. The compiler tarball ships no headers, so as `extern`s
they become `jal` calls (wrong). Need the Psy-Q **`libgte.h`** (or reconstruct the macros) to unblock
this large category.

PAD-module tip: trailing globals (e.g. `DAT_800c0b90..93`) are addressed as offsets into the array
base `DAT_800c0a48` (`lui 0x800c; addiu 0xa48; sb 0x148(v0)`), so reference them as
`((char*)DAT_800c0a48)[0x148]` to match.

Close (near-miss, permuter/scheduling): `Rnd` 20/23, `AddEntry` 30/34 (one commutative operand-order
pattern), `ChoiceIs`, `Mess_TextHeight`. Deferred (hard): CSVector free operators (unaligned
small-struct returns), `Length`/`Normalize` (GTE macros + calls).

Detail of the non-VECTOR exact matches:

| function | module | calls | words |
|---|---|---:|---|
| `FUN_8001d250` (global setter) | MESS | 76 | 3/3 ✅ |
| `Pad_ClearTriggers` (loop) | PAD | 86 | 8/8 ✅ |
| `Mess_SetRGB` (global write) | MESS | 89 | 15/15 ✅ |
| `SFX_Stop` (5-global RMW) | SFX | 25 | 18/18 ✅ |

**Close but needs a permuter** (logic correct; register-allocation/scheduling differs): `Rnd__Fi`
20/23, `ChoiceIs` 7/16, `Mess_TextHeight` 2/19. Pure functions (pointer arith / global RMW) match on
the first/second try; functions with register-allocation freedom or specific scheduling need
permutation.

## Permuter — `tools/permute.mjs` (wired)

An integrated permuter over the same compile+reloc-resolve+score pipeline: it mutates the C
(commutative operand swaps, temp introduction on `x&mask`/`x>>n`/paren subexprs, adjacent
independent-statement reorder) and searches with **simulated annealing + compound mutations** for a
byte-exact variant.

    node tools/permute.mjs <src.c> <addrHex> <size> <syms.json> -O2 --iters N

Mutations: commutative operand swap, temp introduction, adjacent independent **statement *and* temp-
declaration** reorder, and a **cleanup pass** (collapse alias temps, drop unused temps). Search is
simulated annealing with compound mutations; new bests are auto-cleaned.

**Validated to EXACT:** from a 9/15 `Mess_SetRGB` it reached **15/15 byte-exact in 56 iterations**,
autonomously (extract masks → reorder the temp decls to argument order → fix operand order → clean up
redundant temps). So it closes **structural** mismatches (eval order, temporaries, operand/decl
order) to exact on its own.

Boundary: **deep instruction-scheduling** cases it can't express — e.g. `Rnd`'s delayed store (its
three RNG statements are mutually dependent, so no operand-swap/temp/reorder changes GCC's store
placement). Those still need the full AST-based `decomp-permuter-psyq` or hand-tuning.

## Compiler — CONFIRMED: PsyQ 4.5, `-O2 -G0` (globals: `-G8`, gp=0x800d1080)

Found by sweeping every Psy-Q build against `CVector::operator+=`: **`D:\Tools\psyq4.5\CC1PSX.EXE`
(GCC 2.8.1) with `-O2 -G0` reproduces the retail bytes exactly** (THPS1's PSX-EXE has `gp=0` ⇒ -G0).
psyq4.0/4.1 (2.7.2), 4.3/4.4 (other 2.8.1) and 4.6 (2.95.2) all miss — the exact SN build matters.
All compilers run **natively on Windows** (original SN `*.EXE`s, no wibo); `D:\Tools\psyq4.5` also has
`ASPSX.EXE`/`CCPSX.EXE`/`CC1PLPSX.EXE`.

**Canonical matcher:** `node tools/matchcc.mjs <src.c> <retailAddrHex> <size> -O2 -G0` (defaults to
psyq4.5) = compile → `psyq-asm` → byte-diff vs `SLUS_008.60`, printing `N/N >>> EXACT <<<` on a match.

## Byte-exact so far — 14 / 28 VECTOR functions

| function | retail | words |
|---|---|---|
| `CVector::operator+=` | 0x8004da3c | 15/15 ✅ |
| `CVector::operator-=` | 0x8004da78 | 15/15 ✅ |
| `CVector::operator*=(int)` | 0x8004dab4 | 20/20 ✅ |
| `CVector::operator>>=(int)` | 0x8004db54 | 15/15 ✅ |
| `CVector::operator<<=(int)` | 0x8004db90 | 15/15 ✅ |
| `CVector::operator==` | 0x8004dc18 | 17/17 ✅ |
| `CVector::operator!=` | 0x8004dc5c | 18/18 ✅ |
| `CVector::operator-` (unary) | 0x8004df2c | 11/11 ✅ |
| `operator+(CVector,CVector)` | 0x8004dca4 | 22/22 ✅ |
| `operator-(CVector,CVector)` | 0x8004dcfc | 22/22 ✅ |
| `operator*(CVector,int)` | 0x8004dd54 | 26/26 ✅ |
| `operator*(int,CVector)` | 0x8004ddbc | 26/26 ✅ |
| `operator>>(CVector,int)` | 0x8004de8c | 20/20 ✅ |
| `operator<<(CVector,int)` | 0x8004dedc | 20/20 ✅ |

C source in `src/vector/*.c`. Each verified with `matchcc.mjs <c> <addr> <size> -O2 -G0`.

### C-writing patterns learned (essential for matching)
- **Member op returning `CVector&`** (`+=`,`-=`,…): write `V* op(V* this, …){ …; return this; }`
  (the `return *this` produces the leading `move v0,a0`).
- **Free op returning `CVector` by value** (`operator+`, `operator*`, …): write it to return the
  struct **by value** (`V op(…){ V r; r.x=…; return r; }`) — the compiler builds `r` on the stack
  then copies to the hidden return pointer, exactly as retail does. Writing through an explicit
  result pointer does **not** match.
- **Independent loads:** load fields into locals first (`int x=-a->x,y=-a->y,z=-a->z;`) so the
  scheduler hoists them like retail (avoids store-vs-load aliasing conservatism).

### Integer division — SOLVED (`tools/match_div.py`)
Retail uses **bare `div`+`mflo`** (no divide-by-zero/overflow check). cc1 emits the `div $d,$s,$t`
macro; `psyq-asm` can't produce the bare form (it drops `div $zero`/2-op forms), so division functions
go through the **real ASPSX** instead:

1. `cc1psx` → `.s`; 2. rewrite `div $d,$s,$t` → bare **2-operand** `div $s,$t` + `mflo $d`
   (`divu`/`rem`/`remu` likewise, `rem*`→`mfhi`); 3. **`ASPSX.EXE`** assembles it — no check, and it
   inserts the `lw;nop;div` load-delay nops correctly; 4. extract `.text` from the LNK object (length-
   prefixed code record) and byte-diff.

    python tools/match_div.py <src.c> <retailAddrHex> <size> -O2 -G0

Verified EXACT: `CVector::operator/=` (0x8004db04) 20/20, `operator/(CVector,int)` (0x8004de24) 26/26.
(Currently handles pure functions — no reloc resolution in the ASPSX path yet; that's the next add for
division functions that also touch globals/calls.) Unblocks division and the GTE fixed-point fns.

### Remaining VECTOR (12): `Length`/`Normalize` (GTE), `KillSmall`×2, `Mask`, `operator/=`,
`operator%=`(CFriction)×2, and the CSVector (16-bit) variants — matchable with the patterns above
once GTE/CFriction types and the div idiom are handled.
