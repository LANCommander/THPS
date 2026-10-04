# THPS1 matching-decompilation harness

Matching-decomp arm of the project (the readable-C path). Toolchain runs natively on Windows via
Node — no Docker/WSL/Psy-Q-binary needed.

## What works now — full pipeline, all in Node (no Docker/WSL/binaries)

`C source → cc1psx (psyq-wasm) → ASPSX (psyq-asm) → R3000 words → diff vs SLUS_008.60`

- **Compiler:** `psyq-wasm` = PsyQ 4.4 `cc1psx` (GCC 2.8.1), byte-exact vs the real compiler.
- **Assembler:** `psyq-asm` = ASPSX 2.77/2.81-compatible encoder; expands macros and **inserts
  delay-slot / hazard nops** like Sony's assembler.
- **`tools/compile.mjs <src.c> [-O2] [-G0|-G8] [-o out.s]`**: C to assembly through the matchers' own pipeline (CPPPSX + native PsyQ 4.5 cc1, default `-G8`).
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

## Workflow tools

- **`node tools/dis.mjs <addrHex> [size]`** disassembles a retail function for writing C. Call
  targets get their ported demo names, branches get `L<n>` labels, and gp-relative and `lui`-pair
  accesses are resolved to `DAT_xxxxxxxx` (the names to put in `syms.json`).
- **`node tools/m2c.mjs <addrHex> [size] [--asm]`** gives a **first-draft C decompilation** of a retail
  function via [m2c](https://github.com/matt-kempster/m2c). Clone it once with
  `git clone --depth 1 https://github.com/matt-kempster/m2c ../tools/vendor/m2c`; it's gitignored and
  vendors its own pycparser. The bridge emits GNU-as with labels, call names, `%hi/%lo`/`%gp_rel`
  symbol references and bare `div $zero,…`. GTE command words are labelled with their `INLINE_C.H`
  macro (`cop2: gte_sqr0`), and GTE register moves appear as `M2C_ERROR(ctc2 …)` markers. Use it for
  big functions: it gets control flow, switches and arithmetic right, then the README patterns fix
  the codegen details.
- **Diff views for `match_sym.mjs`:** `V=1` gives a full positional side-by-side. **`D=1`** gives an
  alignment-aware diff that LCS-aligns both instruction streams and prints only the differing hunks
  (`@@ mine 103 | retail 104`). Use it on big functions, where one shifted instruction makes the
  positional view useless.
- **Coverage tracker:** **`node tools/progress.mjs`** regenerates **[PROGRESS.md](PROGRESS.md)** with
  totals, history, coverage by size and by module, the closest near-misses and the biggest unmatched
  functions. It also appends to **`progress.csv`** whenever the numbers change. `salvage.py` runs it after
  every merge. `--backfill` rebuilds the history from git. Counting uses `functions.tsv` sizes.
- **`matched.tsv`** is the manifest of every byte-exact function: source, address, size, which
  matcher to use, and the mangled name. **`node tools/check_all.mjs [filter]`** re-verifies them all
  in parallel and exits non-zero on any regression. Run it after any tooling change.
- **`functions.tsv`** lists every retail *game* function (1,189 of them, 0x80010000–0x800858ac; the
  Psy-Q libraries follow, starting after `M3d_PreprocessPulsingColours`) with its size and its demo
  name or `FUN_xxxxxxxx`. Boundaries come from the static recompiler's control-flow analysis and
  agree with the demo SYM sizes for 472 of 474 named functions. `dis.mjs` and `salvage.py` take
  sizes from it, so unnamed functions work like named ones. `check_all.mjs` reports **coverage in
  game-code bytes** (481,452 total).
- `src/unnamed/<addr>.c` holds unnamed functions. The trivial ones (empty bodies, `return K`,
  one-store setters) were generated mechanically from their bytes.
- All matchers use per-process temp files under `build/`, so they can run concurrently.
- **`python tools/salvage.py [--all|--dry-run|paths]`** verifies candidate sources (by default the
  untracked/modified ones under `src/`). Each needs a first-line header `/* <mangledName> (0x<addr>) */`.
  It tries div → sym → cc, appends EXACT rows to `matched.tsv`, and regenerates **`nearmiss.tsv`**
  (≥85%, with scores). Grinding agents write sources, and this merges them.
- **`D=1` for `match_div.py`** too: the same disassembled, LCS-aligned hunk diff as `match_sym.mjs`
  (via `tools/wdiff.mjs`).

## Demo twins: start here for any named function

`build/matches.json` lists the retail functions that are byte-identical to a THPS2-demo function once
relocations and load/store offsets are masked (field offsets can differ: THPS1's `CBody` is 0x2c
bytes bigger, for example). **77 of them were still unmatched (45.8 KB)** when this was found. The
demo's `MAIN.SYM` holds each one's full debug info, and that info decides most of the codegen
choices that blind iteration can't find:

- **`python ../tools/sym_locals.py <name>`** prints the function's parameters, nested blocks and every
  local: its exact C type, its storage class, and the register or stack slot cc1 gave it, in
  declaration order. Write the C with those variables, those types and those scopes.
  `--struct <Tag>` prints a struct/union layout from the SYM's 157k type records. `--lines` prints
  the source line that starts at each word, which splits the retail listing into the original statements.
- **`python ../tools/twin_calls.py <retailAddr> <demoName>`** names every `jal` target from the
  twin's call at the same word, including Psy-Q and `M3dMaths_*` library calls retail leaves as
  `FUN_`. That's half a `syms.json`.
- **Write it as C++** (`src/<module>/<name>.cpp`), since Neversoft's code is C++. A `.cpp` source goes
  through `CC1PLPSX.EXE` with `-fno-exceptions` automatically, in every matcher and in
  `check_all`/`salvage`. Declare `CVector operator-(const CVector&, const CVector&);` and so on, and the
  calls, `const int&` temporaries and by-value returns come out the way retail has them. Wrap SDK
  headers in `extern "C" { }`. Globals the source *defines* land in `.sdata`. Both linkers resolve them
  through their own `syms.json` entries, so no section base is needed.

Results so far: LineLineClosestPoints (1964 B) matched on the 2nd compile. RenderEllipsoid (1940),
PutDataChunk (1956), CTape::AI (1656), Mess_Display, Load8BitBMP2 and Trig_ParseTRGFile matched
within a few iterations each. The last three had been stuck at 97–99% as C.

What the SYM fixed, by function:

- **Intermediate variables.** ParseTRGFile had `char *pNodeName = … + 6;` before the post-increment
  store. Mess_Display stores the scale straight into the global and passes the global. PutDataChunk's
  `PredX/PredY/PredZ` caused retail's odd spill.
- **A shared stack slot.** Block-scoped `CVector Dummy` and `Pos` at the same offset means one variable.
- **Hidden arguments.** In Load8BitBMP2, `bpp` was `printf`'s second argument
  (`"Not 8 bits per pixel, is %d bits per pixel"`).
- **Declaration position.** CTape::AI's `int message_count = 0;` sits *after* the interpolation block.
  Initialising it at the top cost a callee-saved register.
- **`volatile`.** PutDataChunk's vblank counter is re-read each time.

**More patterns from the S18 grind, each verified on retail:**

- **Constants inside both ternary arms.** Write `((c1 ? (c2 ? a : b) : d) << 12) * 3 * 15 / 28` as a
  single expression. gcc then folds the constant into each arm, with a `lui` in the delay slot and an
  `ori` at the head of each arm, as retail does.
- **16-byte stack vectors.** `typedef struct{int x,y,z;} __attribute__((aligned(8))) V;` puts vector
  locals 16 bytes apart. Copy through a plain 12-byte type, or the copy becomes 4 words.
- **`slt; xori; beq`** comes from `m = (a >= b); if (m) …`.
- **6-byte by-value args.** `SV sv = *(SV*)&field; f(sv);` gives the `lwl/lwr` temp plus the `lhu` argument loads.
- **Keeping identical arm tails apart.** When two arms end in the same code, crossjump merges them.
  Give each stage a fresh variable to keep the tails distinct.

Residues these don't explain are local-alloc ties. **The register that `a + b` reuses is the first
operand's.** `&tab[i]` canonicalises to `base + i*4`, so when retail ties the sum to the shifted index,
write `(T *)((i << 2) + (int)base)`. That fixed RenderEllipsoid's `addPrim` and CTape::AI's
`&mMessageTable[n]`.

**More from the S19 grind, each verified on retail:**

- **Callee return types change register allocation.** A call to a function that returns a value is a
  `call_value`, which sets `v0` even when the result is ignored. Declaring a callee `void` when it
  really returns something shifts local-alloc's choices around every call. CCar::AI (1300 B) went from
  322/325 to exact by declaring `Trig_GetPosition` as returning a pointer, and CMenu::Update (904 B)
  from 219/226 by making `SFX_PlayX` return `int`. Check the callee's epilogue for a `v0` write.
  **`tools/retsweep.py`** tries `void`→`int` on every prototype of every near-miss source.
- **Compare-tree switches: fit the case set with `tools/casetree.py`.** It emulates GCC 2.8's
  `group_case_nodes`/`balance_case_nodes`/`emit_case_nodes`, plus the jump optimizer deleting a
  compare whose target matches the jump after it, and checks the predicted compare sequence against
  retail's. Empty `return x;` groups and a case that shares the `default:` label are invisible in the
  bodies but shift the tree's balance. SkipCommand (808 B) needed three such groups, found by searching
  over optional nodes in the value gaps (`casetree.py --s` checks the model against your own build).
- **Shared case tails: write the `goto`.** Two cases whose bodies end the same way get merged by
  cross-jumping, but that happens after register allocation, so duplicated source doubles the shared
  variables' ref counts and changes their registers. `case 1: f(104); goto Bouncy; case 3: f(40);
  Bouncy: …` fixed CPlatform::Bounce's `s2`/`s3` swap.
- **A const global hoisted out of a loop through gp:** declare `extern const int G;` before the
  function and define `extern const int G = 0;` after it. The function body can't fold the value,
  `const` (RTX_UNCHANGING) lets loop.c hoist the load into the preheader, and the definition makes it
  small data, so the load is `lw rX,N(gp)`. A plain global stays in the loop, and a `const` defined
  before use folds to its initializer.
- **Two-statement byte reads:** `v = *p++; v += *p++ << 8;`. Retail increments between the loads, and
  `*p++ + (*p++ << 8)` makes gcc load the same byte twice. The line table shows two lines.
- **Remainders spelled out:** `remx = width - numx * slice_width` gives retail's `mult`+`subu`;
  `width % slice_width` gives `mfhi`. `(n - 1) - a * b` vs `n - (a * b + 1)` changes CSE as well.
- **A variable that dies twice isn't local.** Local-alloc only takes pseudos with exactly one death.
  Reassigning a variable from its own value across several insns (`r = (r << 12) / d;`) gives it two
  deaths, so global-alloc places it instead, usually in a worse register. Use a fresh variable for the
  new value (InitLineInfo's `short Cos2`).
- **The SYM omits some variables.** InitLineInfo's cosines, pack's `numx` and ParsePSX's hoisted
  shift aren't listed, but retail keeps them in registers. If retail holds a value no listed local
  explains, add a local for it.
- **`gte_nop()`** pairs are real source statements: two `nop`s between `gte_ldlzc` and `gte_stlzc`.
- **Constructors as real C++ classes.** Declare the hierarchy with the first polymorphic class's data
  members before its virtual functions, so g++ 2.x puts the vptr after them (CBit at 0x44, CItem at
  0x48). The derived constructor then stores `_vt.<len><Class>`; put that symbol in `syms.json` at the
  vtable's retail address. Members that THPS1 moved can be padded to retail offsets
  (`char pad4c[0x6c - 0x4c];`). The CSmokeJet and CTape constructors matched this way.
- **Mixed running pointer vs. indexed array in a loop:** `mAmp[i] = i ? Length / 80 : 0;` gives a
  running pointer for `mAmp`, where an `if/else` with two stores indexes from `this`.
- **Assigning a parameter moves its prologue copy.** The `move sN,aN` copies are scheduled with
  the register saves, and a parameter the body writes to gets its copy earlier. If retail copies
  `this` before an argument but your build doesn't, stop assigning that argument and use a temporary
  (`int t = -vel; …`), or compute into the member (`mNumSections = NumPoints * 2;` and then use
  `mNumSections`). That fixed the CGlow and CGrindSpark constructors. Writing a constructor as a real
  C++ constructor fixed the CPowerUp one.
- **`new T` with a null check** before the constructor call means the class has its own
  `void *operator new(unsigned int) throw();` (CBit's pool allocator, `__nw__4CBitUi`).
- **A narrow stack argument read late:** pass the parameter straight to the narrower callee
  (`FUN(..., scale)` with a `ushort` parameter). gcc then never copies it at entry, and loop.c hoists
  the `lhu` into the loop preheader as retail does.
- **ADDRESSOF variables are re-read after every store.** A local whose address goes to inline asm
  (`gte_stlvnl2(&zed)`) is an ADDRESSOF pseudo during CSE, and after it is purged its address is based
  on a fresh `$1` (soft frame pointer) rtx that `rtx_varies_p` treats as varying. Every later store
  then invalidates it. If retail reads such a variable once, the source used it once: compute the
  derived value into a local (`int idx = (zed >> 2) & 4095;`). The same effect blocks
  `SlicedImage::pack`'s `dum2`.
- **`OPS=1`** with `D=1` (match_div, via `tools/wdiff.mjs`) aligns on opcodes and immediates only, so
  register noise drops out and only the structural differences are printed. **`DEMO=1 node
  tools/dis.mjs <demoName>`** disassembles the THPS2 demo's version of a function for comparison.
- **`ABS(x)` is a macro:** `(((x) ^ ((x) >> 31)) - ((x) >> 31))`. `abs()` gives a branch.
  `ABS(a) > ABS(b)` loads `a` first, while `ABS(b) < ABS(a)` loads `b` first.
- **Chained assignment stores right to left:** `p.a1 = p.a3 = p.a4 = p.a2 = 0;` emits the stores in
  the order a2, a4, a3, a1, which separate statements never produce (Crowd_Start). Read the store
  order off retail and write the chain backwards.
- **Two array elements loaded with separate `lui`s are two symbols.** If retail loads `X[0].f` and
  `X[1].f` each with its own `lui`/`lw %lo`, declare them as two externs (`DAT_800bf318`,
  `DAT_800bf3d8`). Indexing one array lets CSE share the base address (Card_Write).
- **Store through `reg+off` with the base in a fresh register = an inline member.** Retail's
  `lui a1; addiu a1,%lo(X); sh a0,2094(a1)` comes from `X.SetTime(v)`, where `this` is a pseudo that
  CSE later reuses. `X.mTime = v` folds the offset into the symbol instead.
- **Sin table as a struct:** `struct { short s, c; } T[]; T[a & 4095].s` (or an `int[]` cast to
  `short`) allocates registers differently from `((short *)T)[(a & 4095) * 2]` (CMedal::DoPhysics).
- **Locals the SYM lists as `auto` that retail reaches through `t0`** (`addiu t0,zero,640;
  sw t0,16(sp)`) were spilled by global-alloc. They are not `volatile` and their address isn't
  taken; the reload register `t0` gives them away. Fix the allocation by matching statement order
  and every reference, e.g. a store that CSE folded into one pseudo's address (Card_Write).
- **Load-after-store ordering is not aliasing:** a global load scheduled above a member store in
  retail but not in yours usually means a different statement order (`f234 = Time; f230 = -1;`) or
  an intermediate `base` local (`unsigned *base = Tab; p = base + i;` fixed CamPt's register pair).
  A store of a call result straight from `v0` is grouped with the call by the scheduler, so nothing
  can be placed between them.
- **A global load that retail hoists above member stores → `extern const int G;`.** If retail reads a
  scalar global (e.g. the level index for an `sprintf`) before two `sw zero,off(sN)` member stores
  and yours reads it after, declaring the global `const` (RTX_UNCHANGING) lets the scheduler hoist it.
  This made Competition_ResetMarquee exact and fixed the GameTime load in CScriptOnlyBaddy's
  ExecuteCommand. It does not help when the stalled load is a *member* sitting behind a *global*
  store. For that case, read the member into a local *before* the global store
  (`unsigned snd = mLoopingSound; DAT = …; SFX_ModifyPos(snd, …)`), which made CScriptOnlyBaddy::AI
  exact. Likewise `int n = G; p->h++; G = n + 1;` for a global increment that retail loads before a
  member store (Video_Playback).
- **A value reloaded just before a join, ahead of a global store:** keep it in one local that both
  paths set: `int st = p->m734; if (st == 4 && …) { …calls…; st = p->m734; G = 1; } if (st || …)`.
  The local is dead across the calls, so it stays in a caller-saved register. The reload lands
  before `G = 1` instead of after the join. This made Video_Playback exact.
- **Arguments set up *after* unrelated stores → `do { call(); } while (0);`.** Loop notes are
  scheduling barriers, so a call wrapped in a one-pass loop (probably a macro in the original) keeps
  its `addiu a0/a1` argument setup after the preceding stores. Retail's line table showed a new scope
  starting exactly at the argument setup. That fixed CCamera::ReactToCollision's ApplyMatrixLV block.
- **Unfillable delay slot after a multiply:** cc1 leaves a branch in `.set reorder` for ASPSX, which
  never fills it, when reorg thinks LO is live at the branch target. Reorg scans linearly from the
  previous barrier, and the reload-generated `mflo` (mulsi3's output is `=l`) carries no REG_DEAD
  note, so LO stays "live". A call (which clobbers LO) before the branch makes the fill happen. It is
  still open how retail's ReactToCollision got its `beq …; mult a1,s0`.
- **Delay slot stolen from the branch target ↔ the polarity of the test.** Retail's `beq v0,zero,L;
  addiu s3,zero,-1` (an instruction copied from L, with the branch redirected past it) came from
  `if (!LOS(...)) Index = -1; else { …success… }`. The positive form `if (LOS(...)) {…} else
  Index = -1;` filled the slot from the fall-through instead. This made CamPt_SetClosestCamera exact.
- **Seeing cc1's view:** `CC1PLPSX.EXE x.i -quiet -O2 -fno-exceptions -G8 -dd -o x.s` writes `x.i.dbr`
  (RTL after delayed-branch scheduling, with REG_DEAD/REG_UNUSED notes and live sets). Make `x.i`
  with the CPPPSX line from `tools/match_div.py`.
- **Struct-returning operators written into the destination:** `a = a + b` in C++ builds a temp and
  copies it. Retail's direct-to-destination shape comes from calling the hidden-return operator as
  `extern "C" void alias(T *ret, ...)`, with the alias mapped to the real address in syms.json and
  explicit `int` locals for `const int &` arguments (Shatter_Glass, from 113 to 181 aligned words).
- **CQuat derives from a polymorphic CClass (vptr at +0).** `q = r` is a 5-word copy that re-stores the
  first word last, which accounts for retail's odd `lw v1,vptr; … sw v1,vptr` tail.
- **Five consecutive gp-relative shorts are five separate `short` globals.** A `short[5]` is 10 bytes,
  over the `-G8` limit, so it gets `lui` addressing.
- **Initialise a loop counter after the call before the loop** (`slot = Rnd(); j = 0;`). Initialising
  it before the call keeps it live across the call, which forces an s-register.
- **Use the `_x,_y,_z` inline setter for every stack vector, not just the first.** Plain field stores
  on the later ones shift the stores and registers (CChunkBit ctor).
- **Compare against the value you clamp *from*:** `if (Raw > 2400) Dist = 2400; else Dist = Raw;` puts
  the call result in its own register and the clamped copy in another. `Dist = Raw; if (Dist > ...)`
  merges them.
- **`sll tmp,n,3` before the branch, with `addu v,v,tmp` in its delay slot (in an `a3`/`v1` temp):**
  the pointer advance was written *before* the `if`: `int r = Clip(v, n); v += n; if (!(r & mask))
  { n = p->m; w = v + p->i; …; Draw(w, v, n); }`. Reusing `n` for the next count and computing `w`
  before the inner call give retail's s-register assignment. This made the six M3D render wrappers
  (0x80084d18–0x800850c4) exact.
- **A loop that keeps its entry `j` to the test (not rotated) is a goto loop.** cc1 rotates every
  `while`/`for`, and loop.c then strength-reduces it. Retail loops with `j test` at entry and no
  strength reduction (`buf+i` recomputed in the body) come from `i = 0; goto test; body: …; i++;
  test: if (i < N) goto body;` (FUN_8006ed2c exact; FUN_8004b0e4 at 35/37). An increment in the
  back branch's delay slot is `test: if (j < N) { j++; goto body; }`. No -O/-f flag reproduces it.
- **Several exits sharing one `return r` epilogue (`addu v0,v1,zero` after the restores):** write
  `goto out;` for each exit and put `out: return r;` after the loop. `if (r == -1) return r;`
  constant-folds to `return -1`, and `break` lets cc1 rotate the `for (;;)` (FUN_800604c8). A
  two-case switch after a separate `if` gives retail's linear `beq; beq; j default` chain. A
  three-case switch builds a compare tree instead.
- **An `if (G) x = f(a); else x = f(a);` pair is cross-jumped into one call.** That leaves a
  vestigial `bne …; addu a0,s0,zero` in front of it (FUN_80027d08).
- **Static object construction/teardown (`_GLOBAL_.I/.D`) comes as a pair: one source, `size=` both.**
  Defining `X G;` in a file emits D then I, back to back (FUN_80077060, size=196). An *implicit*
  destructor of a polymorphic class never re-stores its own vptr; only inlined base dtors' stores
  remain. A user-written `~X() {}` does store it. Read the retail vtables (`.word` dtor entries)
  to tie destructors to classes.
- **`ot` local for `addPrim`:** `{ u_long *ot = DAT_800d1a48 + 39; addPrim(ot, p); }` gives retail's
  register choice. Passing `DAT_800d1a48 + 39` straight into the macro doesn't (FUN_80056394).
- **Two globals that are elements of one array get separate `lui` bases:** the second element's
  fields at offset > 0x7fff go through a separate symbol (`extern T DAT_800b09c8;`) while
  `DAT_800a891c[1].on` uses the array (FUN_80048c8c).

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

## Byte-exact functions: `matched.tsv` is the source of truth (820 as of 2026-10-04)

The first 32, by hand:

- **VECTOR / CVector (19):** all 14 operators above + `operator/=`, `operator/(V,int)` (via
  `match_div.py`), `KillSmall`, `Length` (GTE, see below), and `Normalize` (div + call).
- **CSVector (4):** `operator+=`, `operator/=` (div), `Mask`, `KillSmall`.
- **PAD (4):** `Pad_ClearTriggers`, `Pad_LockAnalog`, `Pad_ClearAll`, `Pad_Clear`.
- **M3DUTILS (2):** `M3dUtils_AnglesFromMatrix` (172B, 4 calls incl. `ratan2` — 43/43 first try),
  `M3dUtils_NormaliseVector` (304B: GTE + 3 divs + 2 calls + loop, 76/76 first draft).
- **MESS/SFX/UTILS (3):** `FUN_8001d250` setter, `Mess_SetRGB`, `SFX_Stop`.

Observation: **structured functions with calls/control-flow tend to match on the first try** (call
sequence constrains ordering) — `AnglesFromMatrix` did. The fiddly cases are small register-shuffle
functions (regalloc freedom) and struct-array field offsets (`ReadHooksPacket` needs
`struct S array[]; array[i].field`).

## GTE — UNLOCKED (Psy-Q SDK headers + DMPSX fixup)
GTE code uses Psy-Q's `gte_*` **inline macros** (`INLINE_C.H`). Write the C exactly as Neversoft did:

    #include <sys/types.h>
    #include <libgte.h>
    #include <inline_c.h>
    ... gte_ldlvl(&t); gte_sqr0(); gte_stlvnl(&t); ...

- **Headers** (copyrighted, outside the repo): `D:\Tools\psyq4.5\include\` — the `INCLUDE\` tree from
  the full 4.5 SDK, `archive.org/download/ps1_sdks/PSYQ.SDevTC.Developers.Toolkit.For.PSX.v4.5-MFD.zip`
  (a zip of 7 zips holding a multi-volume RAR; `7z x mfdpsx.rar "INCLUDE\*" -r`). Override the path
  with `PSYQ_INC`.
- **Preprocessing:** cc1 has no cpp (it can't even strip a `/* comment */`), so every matcher
  (`tools/psyq.mjs` → `matchcc`/`match_sym`/`permute`; `match_div.py`) runs **`CPPPSX.EXE`** first,
  as CCPSX does. Comments are fine in sources now.
- **DMPSX:** `INLINE_C.H` emits loads/stores (`lwc2`/`swc2`) directly, but each GTE *command* is a
  placeholder `.word (n<<6)|0x3f` that Sony's **`DMPSX.EXE`** patches into the real `cop2` word
  post-assembly (and it insists on the macro's 2 leading nops). `match_div.py` runs the real
  DMPSX on its ASPSX object; the psyq-asm matchers apply `tools/dmpsx_table.json` (all 65 commands),
  which `tools/gen_dmpsx_table.py` derives by running DMPSX. E.g. `gte_sqr0` `0x00000f3f` → `0x4aa00428`.
- Retail uses the **`INLINE_C.H`** form (the base register is the argument register), not
  `INLINE_O.H` (which routes through `$12`).

Verified: **`CVector::Length` (0x8004d900) 32/32** (`src/vector/length.c`, `match_sym.mjs`) and
**`M3dUtils_NormaliseVector` (0x80081f24) 76/76** (`src/m3dutils/normalisevector.c`, `match_div.py`
since it also divides). Both matched on the first draft. Next: the M3D/physics GTE users.

`Normalize` (0x8004d980) is **not** a GTE function: it's `jal Length` + bare `div`s, 24/24 via
`match_div.py`. Retail never reloads `z`; it stores `(y/len)/len` there, which looks like a bug in the
original source (`v->z = v->y / l`). It's kept as-is for byte-exactness.

PAD-module tip: trailing globals (e.g. `DAT_800c0b90..93`) are addressed as offsets into the array
base `DAT_800c0a48` (`lui 0x800c; addiu 0xa48; sb 0x148(v0)`), so reference them as
`((char*)DAT_800c0a48)[0x148]` to match.

Close (near-miss, permuter/scheduling): `Rnd` 20/23, `AddEntry` 30/34 (one commutative operand-order
pattern), `ChoiceIs`, `Mess_TextHeight`. Deferred (hard): CSVector free operators (unaligned
small-struct returns).

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
**Correction (2026-10-04):** psyq4.5's `CC1PSX -version` banner says **egcs-2.91.66 (egcs 1.1.2)**,
not 2.8.1. 4.3 is 2.8.0 and 4.4 is 2.8.1. Re-checked on CCamera::AI: 4.5 gets 670/671 aligned, 4.4 gets
489 (it uses t0-t2 for block copies where retail uses t1-t3) and 4.6 gets 446. Set `CC1=… CC1PL=…` to
try another build in either matcher; `NOEXC=1` drops `-fno-exceptions` for front ends that lack it.
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

### Patterns from the grind (agent-discovered, each verified on a real match)
- **`v0` vs `v1`/`a2` only:** declare the callee with a non-void return type and ignore the result
  (`int f(void);`, `V* __apl__…`). That reserves `v0` around the call. Try this first.
- **Branch layout:** swap `if (x) return A; return B;` ↔ `if (!x) return B; return A;`. Retail
  often puts the error block first and success last. Use per-branch `return expr>>12;` to stop
  cross-jumping. `if(c)f(a);else f(b);` gives a shared call tail; `?:` doesn't.
- **Rotated list walks** (retail preloads `next`, loops back with `j`):
  `if(!m)return; n=m->next; for(;;){ …; m=n; if(n) n=n->next; else break; }`
- **Switch with a shared tail:** `case 0: …; goto tail; case 1: …; tail: …`.
- **Statement order drives both register assignment and store order.** For about 7 independent
  statements, brute-forcing the permutations works where `permute.mjs` stalls.
- **Arrays:** repeat `DAT[idx].x, DAT[idx].y` instead of taking a `&DAT[idx]` local. Use a
  `short* row = tab[t];` temp for 2-D lookups. Explicit array fields (`h->title[i]`) stop gcc
  strength-reducing loops the way retail didn't. `data[i*w+j].a` matches where
  `data+(idx<<2)` swaps `addu` operands.
- **Arithmetic:** `mult` operand order follows source order. `short s; s = s + (p[i]+1);` gives
  the `andi/sll/sra` sequence, and an explicit `& 0xffff` does not. `/320` by constant is a
  reciprocal `mult`, so `match_sym` handles it with no div.
- **Globals:** use `char X[8];` for gp-relative globals whose *address* is taken (`addiu a0,gp,N`).
  Use `__attribute__((section(".data")))` to force `lui` addressing of a small global. Six-byte
  struct globals copy with `lwl/lwr`. Separate `DAT->field` statements reproduce retail's
  aliasing reloads after `char` stores.
- **Misc:** a never-returning function ends with `for(;;);` (`jal` + self-jump). cc1 is **C89**:
  a declaration after a statement fails with a bare exit 33. If only a `jal` word differs, the
  `syms.json` address is wrong (`target = (w&0x3ffffff)*4 | 0x80000000`).
- **Flip a commutative `addu`'s operand order:** put the intermediate pointer in a named temp:
  `short *s=(short*)(q+o); short *t=s+b; *t=0;`. `s[b]`, `*(s+b)` and `s+=b` all failed.
- **Table base before an index shift** (`lui/addiu` ahead of `sll`): declare it uninitialised and
  assign it after the masking: `SC *b; a&=4095; b=DAT; t=b+a;`.
- **`(size<<4)|flags` words:** declare bitfields (`unsigned flags:4; unsigned len:28;`) and write
  `p->len += …`. The bitfield read-modify-write gives retail's shape directly.
- **Aligned advance:** `len=(sz+3)&~3; buf+=len;` with a temp changes the scheduler tie-break.
- **C++ front end experiment:** `CC1=D:/Tools/psyq4.5/CC1PLPSX.EXE` with the opt string
  `"-O2 -fno-exceptions"` runs through `match_sym.mjs` unchanged. Constructors returning `this` may
  need it (their `move v0,s0` placement differs from C).
- **Same-register `lui rX; addiu rX,rX` (or `lw rX,%lo(rX)`) for a table or global** means the
  declaration was `extern` with a size of **8 bytes or less** (`extern short SinTab[4];`, `extern int G;`).
  cc1 then can't rule out small data, so it emits the `la`/`lw sym` macro and ASPSX expands it
  with one register. Unsized `extern T X[]`, or a real definition, gives cc1's split `lui v0; addiu rX,v0`.
  This fixed `Move__11CWobblyGlow`. The address range doesn't decide it (that sine table is inside
  the gp window); how retail addresses it does. If retail uses `N(gp)`, *define* the global instead.
- **Local pointer to a global struct** (`SComp *c = &DAT_x; c->f…`) stops gcc strength-reducing
  and hoisting in loops (LadderLogic went from 3/95 to exact).
- **Stack locals are laid out in declaration order** (ascending offsets). One temp reused across two
  blocks must be declared once at function scope, or gcc gives it two slots.
- **Stack-passed parameter used several times:** gcc copies it to an s-reg at entry. Reading it
  once late (`short sa = a;` after the calls) reproduces retail's late `lw`.
- **Loops:** `while (!f(x)) {…}` gives jump-to-test-at-bottom (retail's `j L_test`).
  `x/2` on a signed int is `srl/addu/sra`, with no div. For branch polarity, try
  `dx > 0 ? -K : K` vs `dx <= 0 ? K : -K`.
- **Magic divisors** (`mult` + `mfhi` + shift): 0x10624dd3 with `sra 7` = /2000 (`sra 6` = /1000),
  0x2aaaaaab = /6, 0x2e8ba2e9 = /11, 0xfc0fc0fd with `srl 7` = /130.
- **Neversoft's own GTE code** (Medal_Create, Tape_Create) isn't INLINE_C. It's
  `lw; nop; ctc2`/`mtc2` per word, a bare `cop2 0x406012` (rtv0, sf=0) and `swc2 $25..27`. Use inline asm:
  `__asm__ volatile("ctc2 %0, $" #n : : "r"(*(int*)(cam+off)))`, then
  `__asm__ volatile("nop; nop; cop2 0x406012")`, then the `swc2` block with a `"memory"` clobber.
- **Permuter:** `SHOW=1` writes the best variant even when it isn't exact (it took CGlassBit
  from 107 to 136 of 140). It prepends `_tNNN` temps and rewrites the header, so restore line 1 when
  adopting a variant.
- **Split `lui v1; lw v0,off(v1)` (different registers) for a small global:** use `extern int X[];` and
  `X[0]`. (`extern int X;` gives same-register `lui v0; lw v0`.) For an address argument,
  `f(p,&DAT)` with `extern int DAT;` gives retail's `lui a1; addiu a1; jal; move a0` ordering.
- **Destructors:** `*(char**)(p+68)=vtbl; Base(p,0); if(f&1) operator_delete(p);`. Declare the base
  dtor `int` or `void` depending on whether `andi` lands in v0 or v1. A virtual delete is
  `if(o) o->vt->fn((char*)o+o->vt->off,3)`.
- **Frame padding:** a 16-byte frame with no locals or saves needs `volatile int pad[4];`. If the frame
  is 8 bytes short, add `volatile int pad[2];`.
- **Struct copies:** 6-byte → `struct S6 G[1]; G[0]=*p;` (`lwl/lwr`). 12/20-byte `S t=*src;` → loads, then stores.
- **Index arithmetic:** `(struct E*)(i*36+(int)p->e)` gives `addu a0,base` order where `&p->e[i]` doesn't.
- **`<libgpu.h>`** needs `<sys/types.h>` and `<libgte.h>` included first (otherwise cc1 fails with a bare exit 33).
- **Hard for now:** the 64-bit fixed-point MAC helpers (0x80072038–0x800720ec, likely hand-written)
  and Psy-Q packet builders (`addPrim`/`setPolyF4`: logic is right, register naming differs).
- **A load hoisted into a branch delay slot where retail has `nop`:** make the global `volatile`.
  `extern const int G;` does the opposite and lets gcc hoist the load out of a loop that stores.
- **Inline struct "constructors"** (`static inline void VI(V*p,int x,int y,int z){…}`) reproduce retail's
  "x through an sp offset, y/z through a pointer register" store pattern.
- **Many parallel induction pointers** (13 in `ReadControllers`-style loops): index a flat byte array,
  `B[i*364+0x11] || B[i*364+0x21] …`. Struct-array syntax shares one pointer.
- **`addu` tied to the destination:** `dv<<=1; dv+=t;` gives `addu dv,dv,t`. Writing a fresh variable,
  `dw=(unsigned)t+dv;`, gives retail's operand order.
- **Delay-slot ops computed inside the guarded block** (`if(a){u=t&255;…}`), not before it.
- **Loop-back delay slot `move`:** reset `q=p;` at the top of the loop body, not before the loop.
- **Jump-table case base:** `addiu v1,a1,-8448` means the cases start at 8448. Several jump tables in
  one function are fine: each is placed from its own `lui/addiu` pair.
- **Compare-tree switches** (no table): gcc picks the root by cost (ranges count double), so the
  case set, including empty cases, must match exactly to get the same tree.
- **Aggregate locals are emitted where they're declared:** put a 6-byte `lwl/lwr` struct copy in a nested
  `{}` after the earlier calls when retail does it late. Disjoint scopes share a stack slot.
- **Loop keyword matters:** `while(1)`+`break`, `for(;;)` and `do/while` rotate differently. `for(;;)`
  can add a `j` into the middle of the loop.
- **Stack `V` (12-byte) locals sit 16 bytes apart:** add an `int pad;` or use an `aligned(8)` typedef.
- **Struct-returning operators in C:** `V r=__mi__FRC7CVectorT0(&a,&b);`. For a 6-byte CSVector
  result, declare the callee as returning the 12-byte V and copy `*(S6*)&t`. Reusing one V temp
  for both kinds of result fixes the frame size.
- **By-value struct params** (`V a` in a1..a3) need field-wise stores (`d.x=a.x;…`), not `d=a`. A param
  reloaded from its stack home after calls means it was a by-value struct.
- **Aliasing decides re-reads:** a global is re-read after raw `*(short*)(p+o)=` stores, but stays cached
  across typed struct-member stores.
- **`x*340` indexing:** `(char*)D+x*340` gives retail's `sll/addu` chain. `D[x]` with a 340-byte struct
  gives a different multiply.
- **Short/char params retail doesn't sign-extend:** declare them `int` and cast at the point of use.
- **A counter held as both `i` and `i+1`:** two variables, with `j=i+1;` first in the loop body.
- **m2c drafts:** extra call args are often stale registers (check the callee's real signature),
  array strides can be misread, and `SYM + 0xNNNN` artifacts are just the base symbol. Jump tables
  are supported (the bridge emits them as `jtbl_` `.rodata`).
- **Reuse a parameter as the working variable** (`if(a3<0) a3=-a3; else a3=F(p,a1,a3);`) rather than a new local.
- **An argument register passed through unchanged** means the callee takes fewer args than m2c says.
  Declare it `int F(void)` and so on.
- **`nop` in the delay slot before an epilogue jump:** declare the function `int` with no `return`, so gcc
  won't move a `v0` write into the slot.
- **Shared call tails (`goto`/cross-jumps in m2c):** write each call separately (`if(x) F(a,0); else F(b,0);`)
  and gcc merges the tails itself. Store-then-reload of a global: store in each branch and let gcc merge.
- **One hoisted constant reused** (a1 for two stores): a named local assigned once (`one=1;`).
- **Loop guards:** `while(s0&&s0->f!=v){…}` gives the `beq` guard plus a bottom `bne`. A `for` loop gets
  invariant `lui`s hoisted into s-regs and a `goto` loop doesn't.
- **Two shorts 4 bytes apart on the stack:** `short ab[4]`, used as `&ab[0]` and `&ab[2]`. Unused locals vanish
  and shift the layout.
- **`addu` order via staged pointers:** `q=(int*)(a+K); q=(int*)((char*)q+o);` gives `addiu s0,s3,K; addu s0,s0,s1`.
- **A permuter result that reorders calls is wrong**, even when it scores higher. Review before adopting.
- **Retail recomputes `base + i*K` every iteration (no running pointer):** *if the counter has an
  `andi 0xff/0xffff` wrap*, it's an **unsigned narrow type** (`unsigned char`/`unsigned short i`), which stops GCC 2.8
  from strength-reducing it (verified with cc1). With a plain `int` counter (`slti`, no `andi`) that's
  **not** the cause. Several such loops (0x80048ed8, 0x80041ce0, 0x8007171c, 0x800103a4, 0x80010000) mix
  one running pointer, one offset giv and one per-iteration `sll` chain, and no source form has
  reproduced that yet. Struct-array indexing (`E[i]`, `E[1-i]`) with an int `i` did fix 0x80048d24 and 0x80065fec.
- **Sibling loop nests need their own counters** (`j2`/`k2`). Reusing `j`/`k` changes their registers.
- **`&T[i]` written in the loop body** (no pre-declared `p=T`) keeps the `lui` after the loop guard.
  `ptr=&T[x]; f(ptr-1)` keeps the `-4` as a separate `addiu`, whereas `&T[x-1]` folds it.
- **`sh` before `sll/sra`:** `o->s16 = -o->i32; o->i32 = o->s16;` (no `short` temp).
- **Nested `if(s>=20) if(s<25)`** gives retail's `slti/bne; slti/beq`. `a&&b` becomes one `sltiu` range check.
- **Tail-call arg in the delay slot:** `if(!s4)f(2);else f(0);`. `f(s4?0:2)` becomes `sltiu`+`sll`.
- **`for(;;){…; if(v==-1){a=0;continue;} r=v; break;} return r;`** puts `move v0,v1` last in the epilogue.
- **Constant args to inline helpers get folded:** use plain locals (`int h=1,f=1;`) to keep them in registers.
- **Statement-order search pays off:** try all 24 orderings of 4 independent blocks.
- **A variable assigned in two basic blocks becomes a global pseudo**, and global-alloc then picks
  different registers. Use a distinct variable per block (`t1/t2` → `t1/t2` + `u1/u2`). One `a=__nw()` reused
  at 7 call sites became `a1..a7`. This is the biggest lever on large functions.
- **Word-copy loops** (16-byte `lw/sw` blocks) need an int-typed struct (`struct{int c[34];}`). A char
  struct gives `lwl/lwr` plus alignment checks.
- **Typed table index:** `((short*)T)[((x*600)&0x3ff8)>>1]` gives retail's `sll, andi, addu base` with the
  base `lui` first.
- **Manual /4096:** `s0=prod; if(s0<0)s0+=4095; s0>>=12;`. `x*10/12` uses magic 0x2aaaaaab with `sra 1`.
- **Argument evaluation order:** `f(DAT, cond?X:Y)` loads `DAT` before the condition, as retail does.
- **Explicit temps fix `li` order:** `c=386; a=30; G=c; b=-160;`.
- **Prologue order of `move this` vs a stack-arg load**, and the s-reg priority of spilled pseudos versus
  `fp`, are the most common residual diffs on big functions. Nothing so far fixes them reliably.
- **Block-scope vs function-scope declarations** change register allocation for multi-def variables.
  Try every subset of {function-level, block-level}. `Split` went from 435/493 to 492/493 to exact that way.
- **Hidden-return operators** (`__mi__`, `__ml__`, `__pl__`, …) can be declared `void f(T* ret, …)` with the
  result pointer passed explicitly. `*p=f()` makes gcc build a temp and grows the frame.
- **Force a stack slot without `volatile`:** `struct{int sv;int pad;Q r;} z;`. `volatile` blocks delay-slot fill,
  and a 1-element array gets promoted to a register.
- **`x = e + x` comes out as `addu x,x,e`.** Write `n = e + x; x = n;` to get `(e, x)`.
- **`switch` vs if-chain:** `switch(x){case 0:…;break;case 1:…;break;}` with the shared tail *after* the
  switch gives retail's `beq/beq/j` layout. The `if/||` form doesn't.
- **Table search:** `for(i=0;i<6;i++) if(T[i]>=b) break;` gives the non-rotated top-exit loop.
- **Statement-order hill climbing must be dependency-safe:** never move statements across blocks, calls
  or aliasing memory ops. Unsafe climbers raise the score with semantically wrong code.
- **GTE:** `gte_rtv0tr` (0x4a480012) is not `gte_rtv0`. For a cross product use
  `gte_ldopv1/ldopv2/op12/stlvnl`. For a matrix multiply through a `VECTOR` local use `gte_ldlv0`.

**Formerly open tooling gaps, now fixed:**
- **Switch jump tables:** both matchers place a function's own `.rdata` at its retail address.
  The address comes from `syms.json` (`".rdata": "0x…"`) or is inferred from retail's own `lui/addiu`
  pair. The table's contents (entries are `.text` labels) are then **byte-checked against retail**
  too (`.rdata @0x800a23dc: 8/8 words match retail`). The LNK reader also fixes a bug: patch
  offsets are relative to the section's *latest code record*, and a switch splits `.text` in two.
- **`nop` after `mflo`/`mfhi`:** ASPSX treats a *macro-expanded* `mflo/mfhi` like a load and adds a
  `nop` when the next instruction reads the result. A bare `mflo` gets none. The `match_div.py`
  rewrite now emits it. No ASPSX version (2.56–2.86) inserts it for bare `mflo`.
- **`lui` vs gp for a small global:** retail's `lui v1; lw v1,%lo(X)(v1)` (the same register for both)
  comes from **`extern int X;`**, i.e. declared, small and not defined in this file. cc1 then emits the
  `lw $3,X` macro and ASPSX picks `lui`. Defining it gives gp-relative access, and `extern int X[]`
  gives cc1's split `lui $7` + `lw $3`.

### Integer division — SOLVED (`tools/match_div.py`)
Retail uses **bare `div`+`mflo`** (no divide-by-zero/overflow check). cc1 emits the `div $d,$s,$t`
macro; `psyq-asm` can't produce the bare form (it drops `div $zero`/2-op forms), so division functions
go through the **real ASPSX** instead:

1. `cc1psx` → `.s`; 2. rewrite `div $d,$s,$t` → bare **2-operand** `div $s,$t` + `mflo $d`
   (`divu`/`rem`/`remu` likewise, `rem*`→`mfhi`); 3. **`ASPSX.EXE`** assembles it — no check, and it
   inserts the `lw;nop;div` load-delay nops correctly; 4. extract `.text` from the LNK object (length-
   prefixed code record) and byte-diff.

    python tools/match_div.py <src.c> <retailAddrHex> <size> [syms.json] -O2 -G0|-G8

Verified EXACT: `CVector::operator/=` (0x8004db04) 20/20, `operator/(CVector,int)` (0x8004de24) 26/26.
**Relocations are resolved too:** it parses the LNK object (code, patch, XDEF/XREF/XBSS records) and
applies MIPS26/HI16/LO16/GPREL16 patches from the same `syms.json` `match_sym.mjs` takes (the
function's `.text` goes at the target address, so local jumps resolve). All `match_sym` matches
reproduce through it, so it's the one tool that covers **div + GTE + globals/calls** together.
Limitation: the target must be the first function in the file.

### Remaining VECTOR: `operator%=`(CFriction)×2, and the rest of the
CSVector (16-bit) variants. They're matchable with the patterns above once the CFriction types are
handled.
