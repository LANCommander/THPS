#!/usr/bin/env python3
"""
Matcher for DIVISION functions, using the real ASPSX assembler (psyq-asm can't emit bare div).
Pipeline:  cc1psx -> rewrite `div $d,$s,$t` macro to bare `div $s,$t` + `mflo $d` -> ASPSX.EXE ->
extract .text from the LNK object -> byte-diff vs SLUS_008.60.

  python tools/match_div.py <src.c> <retailAddrHex> <sizeBytes> [-O2] [-G0|-G8]

(Pure functions only for now — no relocation resolution. Most math/division fns qualify.)
"""
import re
import struct
import subprocess
import sys
import os

CC1 = r"D:\Tools\psyq4.5\CC1PSX.EXE"
ASPSX = r"D:\Tools\psyq4.5\ASPSX.EXE"
RETAIL = "../extern/thps1_retail/SLUS_008.60"
TEXT_ADDR = 0x80010000
HDR = 0x800

src, addrHex, sizeStr = sys.argv[1], sys.argv[2], sys.argv[3]
addr, size = int(addrHex, 16), int(sizeStr)
opt = next((a for a in sys.argv[4:] if a.startswith("-O")), "-O2")
g = "0" if "-G0" in sys.argv else ("8" if "-G8" in sys.argv else "0")

base = os.path.join("build", f"div_{os.getpid()}")
os.makedirs("build", exist_ok=True)
sfile, rfile, ofile = base + ".s", base + "_rw.s", base + ".obj"

subprocess.run([CC1, src, "-quiet", *opt.split(), f"-G{g}", "-o", sfile], check=True)
s = open(sfile).read()
# div/divu/rem/remu macro -> bare op + mflo/mfhi
s = re.sub(r'^\t(div|divu|rem|remu)\t(\$\w+),(\$\w+),(\$\w+)\s*$',
           lambda m: f'\t{"div" if m.group(1)=="rem" else "divu" if m.group(1)=="remu" else m.group(1)}\t{m.group(3)},{m.group(4)}\n\t{"mfhi" if m.group(1).startswith("rem") else "mflo"}\t{m.group(2)}',
           s, flags=re.M)
open(rfile, "w").write(s)
subprocess.run([ASPSX, rfile, "-o", ofile], check=True, capture_output=True)

obj = open(ofile, "rb").read()
tb = open(RETAIL, "rb").read()[addr - TEXT_ADDR + HDR:][:size]
want = list(struct.unpack_from(f"<{size//4}I", tb, 0))

# Locate .text: anchor on the target's first instruction word (a correct decomp reproduces it);
# fall back to the length-prefixed code record.
code_off = None
anchor = struct.pack("<I", want[0])
idx = obj.find(anchor)
if idx >= 0 and idx + size <= len(obj):
    code_off = idx
else:
    for m in re.finditer(re.escape(struct.pack("<H", size)), obj):
        o = m.end()
        if o + size <= len(obj):
            w0 = struct.unpack_from("<I", obj, o)[0]
            if (w0 >> 26) in (9, 0x23, 0x2b, 0x21, 0x25, 0) and w0 != 0:
                code_off = o
                break
if code_off is None:
    print("could not locate .text in object"); sys.exit(1)
got = list(struct.unpack_from(f"<{size//4}I", obj, code_off))

same = sum(1 for a, b in zip(got, want) if a == b)
if same != len(want) or "-v" in sys.argv:
    for i in range(len(want)):
        mark = "" if got[i] == want[i] else " X"
        print(f"{i:2} {got[i]:08x} | {want[i]:08x}{mark}")
print(f"{same}/{len(want)}" + ("  >>> EXACT <<<" if same == len(want) else ""))
