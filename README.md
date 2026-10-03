# Tony Hawk's Pro Skater (PS1) → Windows

A work-in-progress effort to bring **Tony Hawk's Pro Skater 1** (PlayStation) to Windows by
reverse-engineering its Neversoft engine. The long-term goal is a playable native build; the
current phase is **tooling + analysis** to size the work and choose an approach (matching
decompilation vs. static recompilation).

## Why this is tractable

A Euro demo disc contains an **early build of THPS2 with full Psy-Q debug symbols** — 1,645
typed functions across 98 source files, with 156k C type definitions. THPS1 and THPS2 share the
same engine, so those symbols map (exactly, for the low-level engine; as a guide for the rest)
onto the unsymboled retail THPS1 executable. See **[docs/coverage-report.md](docs/coverage-report.md)**.

## Status (Phase 1)

- ✅ Toolchain: Ghidra 12 + PS1 loader (`ghidra_psx_ldr`) + GhidraMCP, `dumpsxiso`, `chdman`, a
  Psy-Q `.SYM` parser and a demo→retail function matcher (`tools/`).
- ✅ Extracted both executables and the symbol file; parsed the full symbol census.
- ✅ Correlated demo↔retail: **474 functions (31.7%) are byte-identical in retail THPS1** (a
  lower bound), concentrated in the shared engine core.
- 🔄 Matching decompilation (`decomp/`): **25.6% of retail game code is byte-exact C**, with every
  function re-verified against the retail executable. Live numbers, history and per-module coverage
  are in **[decomp/PROGRESS.md](decomp/PROGRESS.md)**.
- ⏭️ Phase 2: import retail into Ghidra with ported names/types; a one-module vertical slice both
  ways to pick the production path.

## Requirements to reproduce

- Ghidra 12.0.3 with the `ghidra_psx_ldr` extension, `dumpsxiso` (mkpsxiso), `chdman`, Python 3.13.
- Your own THPS disc images (nothing copyrighted is included or committed).

See [CLAUDE.md](CLAUDE.md) for the full tooling map and commands.

## Legal

This project contains **no game code or assets**. You must supply your own disc images. Tony
Hawk's Pro Skater is © 1999 Activision / Neversoft. Not affiliated with or endorsed by the
rights holders.
