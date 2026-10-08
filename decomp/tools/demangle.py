#!/usr/bin/env python3
"""Demangle g++ 2.x (GNU v2) symbols with the demangler Ghidra ships, which still supports the old scheme
(modern c++filt dropped it).

  python tools/demangle.py NAME...     print each name and its demangled form
  python tools/demangle.py --tsv       refresh the 5th column ("as written") of functions.tsv

Import demangle(names) -> {mangled: demangled} for other tools. Names that aren't mangled (C functions,
FUN_xxxxxxxx) map to themselves.
"""
import os
import subprocess
import sys

DEMANGLER = os.environ.get(
    "GNU_DEMANGLER", r"D:\Tools\ghidra\GPL\DemanglerGnu\os\win_x86_64\demangler_gnu_v2_24.exe")
HERE = os.path.dirname(os.path.abspath(__file__))
TSV = os.path.join(HERE, "..", "functions.tsv")


def demangle(names):
    names = list(dict.fromkeys(names))
    if not names:
        return {}
    out = subprocess.run([DEMANGLER, "-s", "gnu"], input="\n".join(names) + "\n",
                         capture_output=True, text=True, check=True).stdout.split("\n")
    return {n: (d.strip() or n) for n, d in zip(names, out)}


def refresh_tsv():
    lines = open(TSV, encoding="utf-8", newline="").read().split("\n")
    rows = [(i, l.split("\t")) for i, l in enumerate(lines) if l.startswith("0x")]
    dm = demangle(p[2] for _, p in rows)
    for i, p in rows:
        lines[i] = "\t".join(p[:4] + [dm[p[2]]])
    for i, l in enumerate(lines):
        if l.startswith("# addr\t"):
            lines[i] = "# addr\tsize\tname\tmodule\tas written (demangled by tools/demangle.py --tsv)"
    open(TSV, "w", encoding="utf-8", newline="").write("\n".join(lines))
    print(f"functions.tsv: {sum(1 for _, p in rows if dm[p[2]] != p[2])} of {len(rows)} names demangled")


if __name__ == "__main__":
    if sys.argv[1:] == ["--tsv"]:
        refresh_tsv()
    else:
        for n, d in demangle(sys.argv[1:]).items():
            print(f"{n}\t{d}")
