#!/usr/bin/env python3
"""
Verify candidate sources and merge the byte-exact ones into matched.tsv.

Every source under src/ that isn't in matched.tsv yet (by default, only untracked/modified ones)
must start with the header `/* <mangledName> (0x<addr>) */`. Size comes from retail_names.tsv,
then functions.tsv (or a `size=<n>` note in the header). Each file is tried with div (when the retail bytes contain
a bare div), then sym, then cc; the best score wins.

  python tools/salvage.py [--all] [--dry-run] [paths...]

EXACT rows are appended to matched.tsv. Near-misses (>= 85%) are rewritten into nearmiss.tsv.
"""
import json
import os
import re
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

RETAIL = "../extern/thps1_retail/SLUS_008.60"
NAMES = "../build/retail_names.tsv"
TEXT_ADDR, HDR = 0x80010000, 0x800
GP_STUB = {"gp": "0x800d1080"}
HEADER = re.compile(r"/\*\s*(\S+)\s*\((0x[0-9a-fA-F]{8})\)(?:.*?size=(\d+))?")

args = [a for a in sys.argv[1:] if not a.startswith("--")]
ALL, DRY = "--all" in sys.argv, "--dry-run" in sys.argv

sizes = {}
for line in open(NAMES):
    p = line.strip().split("\t")
    if len(p) == 4 and p[2] == "F": sizes.setdefault(int(p[0], 16), int(p[1]))
for line in open("functions.tsv"):
    p = line.strip().split("\t")
    if len(p) == 3 and not line.startswith("#"): sizes.setdefault(int(p[0], 16), int(p[1]))
matched = {l.split("\t")[1].lower() for l in open("matched.tsv") if l.strip() and not l.startswith("#")}
retail = open(RETAIL, "rb").read()


def candidates():
    if args: return args
    if ALL:
        files = [os.path.join(r, f).replace("\\", "/") for r, _, fs in os.walk("src") for f in fs]
    else:
        out = subprocess.run(["git", "status", "--porcelain", "--untracked-files=all", "src"],
                             capture_output=True, text=True, check=True).stdout
        files = [l[3:].strip().removeprefix("decomp/") for l in out.splitlines() if l[:2] != " D"]
    return sorted(f for f in files if f.endswith(".c") and not f.endswith(".matched.c"))


def has_bare_div(addr, size):
    off = addr - TEXT_ADDR + HDR
    for i in range(0, size, 4):
        w = struct.unpack_from("<I", retail, off + i)[0]
        if w >> 26 == 0 and (w & 0x3F) in (0x1A, 0x1B): return True
    return False


def run(cmd):
    r = subprocess.run(cmd, capture_output=True, text=True)
    last = (r.stdout.strip().splitlines() or [""])[-1]
    m = re.match(r"(\d+)/(\d+)", last)
    return (int(m.group(1)), int(m.group(2)), "EXACT" in last) if m else (0, 1, False)


def attempt(src):
    head = open(src, encoding="utf8", errors="replace").readline()
    m = HEADER.search(head)
    if not m: return src, None, "no header"
    name, addr = m.group(1), int(m.group(2), 16)
    size = int(m.group(3)) if m.group(3) else sizes.get(addr)
    if not size: return src, None, f"unknown size for {addr:#x}"
    if f"{addr:#010x}" in matched: return src, None, "already in matched.tsv"
    syms = src[:-2] + ".syms.json"
    stub = None
    if not os.path.exists(syms):
        stub = f"build/stub_{os.getpid()}_{abs(hash(src))}.json"
        json.dump(GP_STUB, open(stub, "w"))
    sp = syms if stub is None else stub
    tries = {
        "div": ["python", "tools/match_div.py", src, hex(addr), str(size), *([syms] if stub is None else []), "-O2", "-G8"],
        "sym": ["node", "tools/match_sym.mjs", src, hex(addr), str(size), sp, "-O2"],
        "cc": ["node", "tools/matchcc.mjs", src, hex(addr), str(size), "-O2", "-G0"],
    }
    order = ["div", "sym", "cc"] if has_bare_div(addr, size) else ["sym", "cc", "div"]
    best = None
    for tool in order:
        got, total, exact = run(tries[tool])
        if best is None or got > best[1]: best = (tool, got, total, exact)
        if exact: break
    if stub:
        if best[0] == "sym" and best[3] and not DRY: json.dump(GP_STUB, open(syms, "w"))
        os.remove(stub)
    tool, got, total, exact = best
    return src, dict(name=name, addr=addr, size=size, tool=tool, got=got, total=total, exact=exact), None


os.makedirs("build", exist_ok=True)
files = candidates()
with ThreadPoolExecutor(max(1, (os.cpu_count() or 2) - 1)) as ex:
    results = list(ex.map(attempt, files))

exact, near, fail, skip = [], [], [], []
for src, r, why in results:
    if r is None: skip.append((src, why)); continue
    pct = r["got"] / r["total"]
    (exact if r["exact"] else near if pct >= 0.85 else fail).append((src, r))
for src, r in exact: print(f"EXACT {src:48} {r['got']}/{r['total']} ({r['tool']})")
for src, r in near: print(f"near  {src:48} {r['got']}/{r['total']} ({r['tool']})")
for src, r in fail: print(f"miss  {src:48} {r['got']}/{r['total']} ({r['tool']})")
for src, why in skip: print(f"skip  {src:48} {why}")
print(f"\n{len(exact)} exact, {len(near)} near (>=85%), {len(fail)} miss, {len(skip)} skipped")

if not DRY:
    if exact:
        with open("matched.tsv", "a", encoding="utf8", newline="") as f:
            for src, r in sorted(exact, key=lambda e: e[0]):
                f.write(f"{src}\t{r['addr']:#010x}\t{r['size']}\t{r['tool']}\t{r['name']}\n")
    # nearmiss.tsv is a regenerated view: keep entries for files not re-checked this run, minus
    # anything that has become exact since
    keep = []
    now_matched = {l.split("\t")[1].lower() for l in open("matched.tsv") if l.strip() and not l.startswith("#")}
    if os.path.exists("nearmiss.tsv"):
        checked = {src for src, _, _ in results}
        keep = [l for l in open("nearmiss.tsv") if l.strip() and not l.startswith("#")
                and l.split("\t")[0] not in checked and l.split("\t")[1].lower() not in now_matched]
    tmp = f"build/nearmiss_{os.getpid()}.tsv"
    with open(tmp, "w", encoding="utf8", newline="") as f:
        f.write("# Logic-correct candidates that aren't byte-exact yet (regenerated by tools/salvage.py)\n")
        f.write("# src\taddr\tsize\ttool\tscore\n")
        f.writelines(keep)
        for src, r in sorted(near, key=lambda e: e[0]):
            f.write(f"{src}\t{r['addr']:#010x}\t{r['size']}\t{r['tool']}\t{r['got']}/{r['total']}\n")
    # agents may be reading nearmiss.tsv concurrently (Windows sharing locks): retry the swap briefly
    import time
    for attempt in range(20):
        try: os.replace(tmp, "nearmiss.tsv"); break
        except OSError: time.sleep(0.5)
    else: print(f"warning: nearmiss.tsv locked; new view left at {tmp}")
