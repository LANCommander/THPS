#!/usr/bin/env python3
"""
Estimate how much of the symbol-rich THPS2 demo (PROSKATE.EXE + MAIN.SYM) maps onto
the unsymboled retail THPS1 (SLUS_008.60), for the Phase-1 coverage report.

Method (a lightweight, defensible BSim analog):
  * Read the demo's function table (addr, size, name, file) from the parsed SYM json.
  * Extract each demo function's raw MIPS from PROSKATE.EXE and NORMALIZE it: mask the
    fields that move under relocation / a different link base (j/jal 26-bit target;
    the low-16 immediate of lui/addiu/ori and every load/store). Relative branch
    offsets are kept (they are stable when the code shape is identical).
  * Do the same, instruction by instruction, over the whole retail .text, and index it.
  * EXACT-SHAPE match: a demo function whose full normalized instruction sequence occurs
    verbatim in retail is almost certainly the same function (ancestor). This is a strict
    LOWER BOUND on shared code (THPS1 is older, so many functions evolved slightly).
  * FUZZY match (sample): best-aligned instruction-level similarity >= threshold catches
    evolved functions. Reported on a sample to bound the upper side.

Usage: python tools/match_functions.py
"""
import json
import os
import struct

DEMO_EXE = "extern/demo/PROSKATE.EXE"
DEMO_TEXT_ADDR = 0x80018000
RETAIL_EXE = "extern/thps1_retail/SLUS_008.60"
RETAIL_TEXT_ADDR = 0x80010000
PSX_HDR = 0x800
SYM_JSON = "build/MAIN_sym.json"

MIN_INSNS = 6          # ignore tiny stubs for the headline number
FUZZY_SAMPLE = 400
FUZZY_THRESH = 0.90

# opcodes whose low-16 immediate encodes an address fragment / is link-sensitive
MASK_LO16_OPS = {0x0f, 0x09, 0x0d} | set(range(0x20, 0x30)) | set(range(0x30, 0x40))


def norm_insn(w):
    op = w >> 26
    if op in (0x02, 0x03):          # J / JAL -> keep opcode only
        return op << 26
    if op in MASK_LO16_OPS:         # lui/addiu/ori/loads/stores -> mask imm16
        return w & 0xFFFF0000
    return w                        # R-type, branches, etc. kept whole


def load_text(path, text_addr):
    d = open(path, "rb").read()
    body = d[PSX_HDR:]
    n = len(body) // 4
    words = struct.unpack_from("<%dI" % n, body, 0)
    return list(words), text_addr


def norm_stream(words):
    return [norm_insn(w) for w in words]


def main():
    j = json.load(open(SYM_JSON))
    funcs = [f for f in j["funcs"] if f["size"] and f["size"] >= MIN_INSNS * 4]

    dwords, dbase = load_text(DEMO_EXE, DEMO_TEXT_ADDR)
    rwords, rbase = load_text(RETAIL_EXE, RETAIL_TEXT_ADDR)
    rnorm = norm_stream(rwords)

    # index retail by an 8-instruction normalized window -> start positions
    K = 8
    index = {}
    for i in range(len(rnorm) - K + 1):
        key = tuple(rnorm[i:i + K])
        index.setdefault(key, []).append(i)

    def demo_norm_func(f):
        off = (f["addr"] - dbase) // 4
        n = f["size"] // 4
        return [norm_insn(w) for w in dwords[off:off + n]]

    exact = []
    per_file = {}
    total_bytes = 0
    matched_bytes = 0
    demo_funcs_norm = {}
    for f in funcs:
        sig = demo_norm_func(f)
        demo_funcs_norm[f["addr"]] = sig
        total_bytes += f["size"]
        pf = per_file.setdefault(f["file"].replace("\\", "/").split("/")[-1],
                                 {"n": 0, "m": 0, "b": 0, "mb": 0})
        pf["n"] += 1
        pf["b"] += f["size"]
        if len(sig) < K:
            continue
        hit = False
        for pos in index.get(tuple(sig[:K]), ()):
            if rnorm[pos:pos + len(sig)] == sig:
                hit = True
                f["retail_addr"] = rbase + pos * 4
                break
        if hit:
            exact.append(f)
            matched_bytes += f["size"]
            pf["m"] += 1
            pf["mb"] += f["size"]

    # fuzzy pass on a sample of the UNMATCHED functions
    unmatched = [f for f in funcs if f not in exact]
    sample = unmatched[:FUZZY_SAMPLE]
    fuzzy_hits = 0
    for f in sample:
        sig = demo_funcs_norm[f["addr"]]
        if len(sig) < K:
            continue
        best = 0.0
        cand = set()
        # gather candidate alignments from any shared 8-window
        for w in range(0, len(sig) - K + 1, max(1, (len(sig) - K) // 4 or 1)):
            for pos in index.get(tuple(sig[w:w + K]), ()):
                cand.add(pos - w)
        for start in cand:
            if start < 0 or start + len(sig) > len(rnorm):
                continue
            same = sum(1 for a, b in zip(sig, rnorm[start:start + len(sig)]) if a == b)
            best = max(best, same / len(sig))
            if best >= 0.999:
                break
        if best >= FUZZY_THRESH:
            fuzzy_hits += 1

    n = len(funcs)
    print(f"=== demo(THPS2) -> retail THPS1 function correlation ===")
    print(f"demo functions considered (>= {MIN_INSNS} insns): {n}  ({total_bytes:,} bytes)")
    print(f"EXACT-shape matches in retail : {len(exact)}  ({len(exact)/n*100:.1f}% of funcs, "
          f"{matched_bytes/total_bytes*100:.1f}% of bytes)")
    fs = len(sample)
    print(f"FUZZY (>= {int(FUZZY_THRESH*100)}%) on {fs} sampled unmatched: {fuzzy_hits} "
          f"({fuzzy_hits/fs*100:.1f}% of sample) -> extra evolved-but-shared functions")
    est_total = len(exact) + (fuzzy_hits / fs) * len(unmatched) if fs else len(exact)
    print(f"extrapolated shared functions  : ~{est_total:.0f} / {n}  (~{est_total/n*100:.0f}%)")

    print("\n--- match rate by module (exact), modules with >=8 funcs ---")
    rows = [(k, v) for k, v in per_file.items() if v["n"] >= 8]
    rows.sort(key=lambda kv: -kv[1]["n"])
    print(f"{'module':<20}{'funcs':>6}{'exact':>6}{'rate':>6}")
    for k, v in rows:
        print(f"{k[:19]:<20}{v['n']:>6}{v['m']:>6}{v['m']/v['n']*100:>5.0f}%")

    json.dump({"exact_matches": [{"demo_addr": f["addr"], "retail_addr": f.get("retail_addr"),
               "name": f["name"], "file": f["file"], "size": f["size"]} for f in exact]},
              open("build/matches.json", "w"), indent=1)
    print("\nwrote build/matches.json")


if __name__ == "__main__":
    main()
