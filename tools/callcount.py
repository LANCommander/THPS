#!/usr/bin/env python3
"""
Rank retail THPS1 functions by how often they are called (direct JAL targets),
to prioritise decompilation by impact. Annotates with demo-derived names.

  python tools/callcount.py [N]
"""
import json
import struct
import sys
from collections import Counter

RETAIL = "extern/thps1_retail/SLUS_008.60"
TEXT_ADDR = 0x80010000
HDR = 0x800

data = open(RETAIL, "rb").read()
body = data[HDR:]
nwords = len(body) // 4
words = struct.unpack_from("<%dI" % nwords, body, 0)

calls = Counter()      # target addr -> direct call count
jalr = 0               # indirect calls (can't attribute)
for i, w in enumerate(words):
    op = w >> 26
    if op == 3:        # JAL
        pc = TEXT_ADDR + i * 4
        target = (pc & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
        calls[target] += 1
    elif op == 0 and (w & 0x3F) == 0x09:   # JALR
        jalr += 1

# names: demo exact-match names ported to retail addresses
names = {}
files = {}
sizes = {}
try:
    for e in json.load(open("build/matches.json"))["exact_matches"]:
        if e.get("retail_addr"):
            names[e["retail_addr"]] = e["name"]
            files[e["retail_addr"]] = e["file"].replace("\\", "/").split("/")[-1]
            sizes[e["retail_addr"]] = e["size"]
except FileNotFoundError:
    pass

n = int(sys.argv[1]) if len(sys.argv) > 1 else 60
ranked = calls.most_common()
total_calls = sum(calls.values())
named_in = sum(1 for a in calls if a in names)
print(f"retail .text: {nwords:,} words, {len(calls):,} distinct direct-call targets, "
      f"{total_calls:,} direct calls, {jalr:,} indirect (jalr)")
print(f"named (demo exact-match) among call targets: {named_in}/{len(calls)}\n")

print(f"{'rank':>4} {'calls':>5} {'addr':>10} {'sz':>4}  name / module")
for rank, (addr, c) in enumerate(ranked[:n], 1):
    nm = names.get(addr)
    if nm:
        tag = f"{nm}   [{files.get(addr,'?')}]"
        sz = sizes.get(addr, 0)
    else:
        tag = "(unnamed — identify via demo/Ghidra)"
        sz = 0
    print(f"{rank:>4} {c:>5} 0x{addr:08x} {sz:>4}  {tag}")

# summary: how many of the top-100 are named game funcs
top = ranked[:100]
named_top = sum(1 for a, _ in top if a in names)
print(f"\nof the top 100 most-called: {named_top} are demo-named game functions, "
      f"{100 - named_top} unnamed (library or unmatched game code).")
