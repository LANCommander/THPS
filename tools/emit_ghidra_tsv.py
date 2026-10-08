#!/usr/bin/env python3
"""
Emit TSVs that ghidra_scripts/ApplyPsxSym.java consumes in headless mode.

  build/demo_syms.tsv     from build/MAIN_sym.json   -> names for the demo (PROSKATE.EXE)
  build/retail_names.tsv  from build/matches.json    -> demo names ported onto retail THPS1

TSV columns: addr(hex)  size  kind(F|D)  name
"""
import json
import os

os.makedirs("build", exist_ok=True)

# demo: every function-start record -> F ; plain symbols -> D (skip if same addr as a func)
j = json.load(open("build/MAIN_sym.json"))
func_addrs = {f["addr"] for f in j["funcs"]}
with open("build/demo_syms.tsv", "w") as fh:
    for f in j["funcs"]:
        fh.write(f"0x{f['addr']:08x}\t{f['size'] or 0}\tF\t{f['name']}\n")
    for s in j["symbols"]:
        if s["addr"] not in func_addrs:
            fh.write(f"0x{s['addr']:08x}\t0\tD\t{s['name']}\n")
print("wrote build/demo_syms.tsv",
      f"({len(j['funcs'])} funcs + {len(j['symbols'])} syms)")

# retail: exact-matched demo functions, named at their retail address
if os.path.exists("build/matches.json"):
    mj = json.load(open("build/matches.json"))
    m = mj["exact_matches"]
    # label-only symbols (asm entry points, library code, data) go in as D: a label, never a
    # created function, since the span may be data
    labels = mj.get("label_matches", [])
    # globals named from their demo twins (tools/data_names.py)
    data = []
    if os.path.exists("decomp/data_names.tsv"):
        data = [l.split("\t")[:2] for l in open("decomp/data_names.tsv", encoding="utf-8") if l.startswith("0x")]
    with open("build/retail_names.tsv", "w") as fh:
        for e in m:
            if e.get("retail_addr"):
                fh.write(f"0x{e['retail_addr']:08x}\t{e['size']}\tF\t{e['name']}\n")
        for e in labels:
            fh.write(f"0x{e['retail_addr']:08x}\t0\tD\t{e['name']}\n")
        for a, n in data:
            fh.write(f"{a}\t0\tD\t{n}\n")
    print("wrote build/retail_names.tsv",
          f"({sum(1 for e in m if e.get('retail_addr'))} funcs + {len(labels)} labels + {len(data)} globals)")
