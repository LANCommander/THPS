#!/usr/bin/env python3
"""
Derive the DMPSX placeholder -> GTE `cop2` table by running Sony's real DMPSX.EXE.

Psy-Q's INLINE_C.H emits every GTE *command* (rtps, sqr0, nclip, ...) as a placeholder
`.word (n<<6)|0x3f` (SPECIAL, funct 0x3f); DMPSX.EXE patches those into the real cop2 words in the
object file after assembly. psyq-asm has no DMPSX, so the matchers apply this table instead.

  python tools/gen_dmpsx_table.py      (writes tools/dmpsx_table.json)

Needs the SDK headers in PSYQ_INC (default D:/Tools/psyq4.5/include) plus ASPSX.EXE/DMPSX.EXE.
"""
import json
import os
import re
import struct
import subprocess

PSYQ = r"D:\Tools\psyq4.5"
INC = os.environ.get("PSYQ_INC", os.path.join(PSYQ, "include"))
HERE = os.path.dirname(os.path.abspath(__file__))
SENTINEL = 0x12345678

ph = set()
for h in ("INLINE_C.H", "INLINE_O.H"):
    ph |= {int(x, 16) for x in re.findall(r"\.word\s+(0x[0-9a-fA-F]+)", open(os.path.join(INC, h)).read())}
ph = sorted(p for p in ph if p & 0xFC00003F == 0x3F)

# DMPSX insists on two nops ahead of each command (the macros provide them), so frame each one.
os.makedirs("build", exist_ok=True)
s = "\t.text\n\t.set noreorder\n" + "".join(f"\t.word 0x{SENTINEL:08x}\n\tnop\n\tnop\n\t.word 0x{p:08x}\n" for p in ph)
open("build/dmpsx_probe.s", "w").write(s)
subprocess.run([os.path.join(PSYQ, "ASPSX.EXE"), "build/dmpsx_probe.s", "-o", "build/dmpsx_probe.obj"],
               check=True, capture_output=True)
subprocess.run([os.path.join(PSYQ, "DMPSX.EXE"), "build/dmpsx_probe.obj", "-o", "build/dmpsx_probe_out.obj"],
               check=True, capture_output=True)

obj = open("build/dmpsx_probe_out.obj", "rb").read()
base = obj.find(struct.pack("<I", SENTINEL))
table = {}
for k, p in enumerate(ph):
    assert struct.unpack_from("<I", obj, base + 16 * k)[0] == SENTINEL, "object layout moved"
    table[f"0x{p:08x}"] = f"0x{struct.unpack_from('<I', obj, base + 16 * k + 12)[0]:08x}"

out = os.path.join(HERE, "dmpsx_table.json")
json.dump(table, open(out, "w"), indent=1)
print(f"wrote {out}: {len(table)} GTE commands")
