#!/usr/bin/env python3
"""
Name a retail function's call targets (and lui/addiu data refs) from its THPS2-demo twin.

  python tools/twin_calls.py <retailAddrHex> <demoFuncName-substring>

The twin has the same code, so a jal at word i in retail calls the same function the demo's jal at
word i does, and the demo SYM names it (Psy-Q library functions like SetRotMatrix included).
Prints `retail_target demo_name` pairs, ready for a syms.json.
"""
import json, os, struct, sys

ROOT = os.path.join(os.path.dirname(__file__), "..")
demo = open(os.path.join(ROOT, "extern/demo/PROSKATE.EXE"), "rb").read()
ret = open(os.path.join(ROOT, "extern/thps1_retail/SLUS_008.60"), "rb").read()
sym = json.load(open(os.path.join(ROOT, "build/MAIN_sym.json")))
names = {}
for s in sym["symbols"]: names.setdefault(s["addr"], s["name"])
for f in sym["funcs"]: names[f["addr"]] = f["name"]
raddr = int(sys.argv[1], 16)
f = next(f for f in sym["funcs"] if sys.argv[2] in f["name"])
n = f["size"] // 4
dw = struct.unpack_from(f"<{n}I", demo, f["addr"] - 0x80018000 + 0x800)
rw = struct.unpack_from(f"<{n}I", ret, raddr - 0x80010000 + 0x800)
out = {}
for i in range(n):
    if dw[i] >> 26 == 3 and rw[i] >> 26 == 3:
        dt, rt = (dw[i] & 0x3FFFFFF) << 2 | 0x80000000, (rw[i] & 0x3FFFFFF) << 2 | 0x80000000
        out[f"0x{rt:08x}"] = names.get(dt, f"?{dt:#x}")
for k, v in sorted(out.items()): print(k, v)
