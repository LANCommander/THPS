#!/usr/bin/env python3
"""
Matcher for DIVISION functions, using the real ASPSX assembler (psyq-asm can't emit bare div).
Pipeline:  cc1psx -> rewrite `div $d,$s,$t` macro to bare `div $s,$t` + `mflo $d` -> ASPSX.EXE ->
DMPSX (GTE sources) -> parse the LNK object, resolve its patches -> byte-diff vs SLUS_008.60.

  python tools/match_div.py <src.c> <retailAddrHex> <sizeBytes> [syms.json] [-O2] [-G0|-G8]

syms.json is the same map match_sym.mjs takes ({"gp":..,"<name>":"0x.."}); the function's own .text
is placed at the target address, so local jumps resolve too. Assumes the target is the first
function in the file.
"""
import json
import re
import struct
import subprocess
import sys
import os

CC1 = r"D:\Tools\psyq4.5\CC1PSX.EXE"
ASPSX = r"D:\Tools\psyq4.5\ASPSX.EXE"
CPP = r"D:\Tools\psyq4.5\CPPPSX.EXE"
DMPSX = r"D:\Tools\psyq4.5\DMPSX.EXE"
INC = os.environ.get("PSYQ_INC", r"D:\Tools\psyq4.5\include")
# what CCPSX hands cpp for C on the PSX target (mirrors tools/psyq.mjs)
CPP_DEFS = ["-undef", "-D__GNUC__=2", "-D__OPTIMIZE__", "-Dmips", "-D__mips__", "-D__psx__", "-D_LANGUAGE_C"]
RETAIL = "../extern/thps1_retail/SLUS_008.60"
TEXT_ADDR = 0x80010000
HDR = 0x800

src, addrHex, sizeStr = sys.argv[1], sys.argv[2], sys.argv[3]
addr, size = int(addrHex, 16), int(sizeStr)
symPath = next((a for a in sys.argv[4:] if a.endswith(".json")), None)
syms = json.load(open(symPath)) if symPath else {}
opt = next((a for a in sys.argv[4:] if a.startswith("-O")), "-O2")
g = "0" if "-G0" in sys.argv else ("8" if "-G8" in sys.argv else "0")

base = os.path.join("build", f"div_{os.getpid()}")
os.makedirs("build", exist_ok=True)
sfile, rfile, ofile = base + ".s", base + "_rw.s", base + ".obj"

# cc1 has no preprocessor (not even comment stripping), so always run CPPPSX first, as CCPSX does
csrc = base + ".i"
subprocess.run([CPP, *CPP_DEFS, "-I", INC, src, csrc], check=True, capture_output=True)
subprocess.run([CC1, csrc, "-quiet", *opt.split(), f"-G{g}", "-o", sfile], check=True)
s = open(sfile).read()
# div/divu/rem/remu macro -> bare op + mflo/mfhi
s = re.sub(r'^\t(div|divu|rem|remu)\t(\$\w+),(\$\w+),(\$\w+)\s*$',
           lambda m: f'\t{"div" if m.group(1)=="rem" else "divu" if m.group(1)=="remu" else m.group(1)}\t{m.group(3)},{m.group(4)}\n\t{"mfhi" if m.group(1).startswith("rem") else "mflo"}\t{m.group(2)}',
           s, flags=re.M)
open(rfile, "w").write(s)
subprocess.run([ASPSX, rfile, "-o", ofile], check=True, capture_output=True)
# INLINE_C.H GTE commands are `.word (n<<6)|0x3f` placeholders; DMPSX patches them into cop2 in place
if re.search(r"\.word\s+0x0000[0-9a-fA-F]{4}", s):
    subprocess.run([DMPSX, ofile, "-b"], check=True, capture_output=True)

tb = open(RETAIL, "rb").read()[addr - TEXT_ADDR + HDR:][:size]
want = list(struct.unpack_from(f"<{size//4}I", tb, 0))


def read_lnk(path):
    """Parse a Psy-Q LNK object: per-section code bytes, patches, and symbol id -> name/location."""
    b = open(path, "rb").read()
    assert b[:3] == b"LNK", "not a Psy-Q LNK object"
    i = 4
    u8 = lambda: b[i]
    code, sect_names, names, local, patches = {}, {}, {}, {}, []
    cur = None

    def take(fmt):
        nonlocal i
        v = struct.unpack_from("<" + fmt, b, i); i += struct.calcsize("<" + fmt); return v

    def pstr():
        nonlocal i
        n = b[i]; i += 1; v = b[i:i + n].decode("latin-1"); i += n; return v

    def expr():
        (op,) = take("B")
        if op == 0x00: return ("const", take("I")[0])
        if op == 0x02: return ("sym", take("H")[0])
        if op == 0x04: return ("sect", take("H")[0])
        if op in (0x2C, 0x2E): return ("+" if op == 0x2C else "-", expr(), expr())
        raise ValueError(f"unknown LNK expression op 0x{op:02x} at {i - 1:#x}")

    while True:
        (rec,) = take("B")
        if rec == 0x00: break
        elif rec == 0x02:
            (n,) = take("H"); code.setdefault(cur, bytearray()).extend(b[i:i + n]); i += n
        elif rec == 0x06: (cur,) = take("H")
        elif rec == 0x08: take("I")                                          # uninitialised space
        elif rec == 0x0A:
            t, off = take("BH"); patches.append((cur, t, off, expr()))
        elif rec == 0x0C:
            sid, sec, off = take("HHI"); names[sid] = pstr(); local[sid] = (sec, off)
        elif rec == 0x0E: (sid,) = take("H"); names[sid] = pstr()
        elif rec == 0x10: sid, _, _ = take("HHB"); sect_names[sid] = pstr()
        elif rec == 0x12: take("HI"); pstr()                                 # local symbol
        elif rec == 0x1C: take("H"); pstr()                                  # source file name
        elif rec == 0x2E: take("B")                                          # processor type
        elif rec == 0x30: sid, _, _ = take("HHI"); names[sid] = pstr()       # XBSS (common)
        elif rec == 0x3C: take("H")
        elif rec == 0x4A: take("HIHIHIHIi"); pstr()                          # function start
        elif rec in (0x4C, 0x4E, 0x50): take("HII")                          # function end, block start/end
        else: raise ValueError(f"unknown LNK record 0x{rec:02x} at {i - 1:#x}")
    return code, sect_names, names, local, patches


code, sect_names, names, local, patches = read_lnk(ofile)
text = next(k for k, v in sect_names.items() if v == ".text")
buf = code.get(text, bytearray())
if len(buf) < size:
    print(f"object .text is {len(buf)} bytes, target is {size}"); sys.exit(1)

# Linker-lite, as in match_sym.mjs: .text sits at the target address, externs come from syms.json.
gp = int(syms.get("gp", "0"), 16)


def sym_addr(sid):
    n = names.get(sid)
    if n in syms: return int(syms[n], 16)
    if sid in local and local[sid][0] == text: return addr + local[sid][1]
    raise KeyError(f"unknown symbol {n!r} (add it to syms.json)")


def ev(e):
    if e[0] == "const": return e[1]
    if e[0] == "sym": return sym_addr(e[1])
    if e[0] == "sect":
        if e[1] == text: return addr
        raise KeyError(f"reference into section {sect_names.get(e[1])} (define it via syms.json)")
    return ev(e[1]) + ev(e[2]) if e[0] == "+" else ev(e[1]) - ev(e[2])


for sec, t, off, e in patches:
    if sec != text or off >= size: continue
    v, (w,) = ev(e) & 0xFFFFFFFF, struct.unpack_from("<I", buf, off)
    if t == 74:    w = (w & 0xFC000000) | ((v >> 2) & 0x03FFFFFF)             # j/jal target
    elif t == 82:  w = (w & 0xFFFF0000) | (((v + 0x8000) >> 16) & 0xFFFF)      # HI16 (paired carry)
    elif t == 84:  w = (w & 0xFFFF0000) | (v & 0xFFFF)                         # LO16
    elif t == 100: w = (w & 0xFFFF0000) | ((v - gp) & 0xFFFF)                  # GPREL16
    else: raise ValueError(f"unhandled LNK patch type {t} at .text+{off:#x}")
    struct.pack_into("<I", buf, off, w)
got = list(struct.unpack_from(f"<{size//4}I", buf, 0))

same = sum(1 for a, b in zip(got, want) if a == b)
if same != len(want) or "-v" in sys.argv:
    for i in range(len(want)):
        mark = "" if got[i] == want[i] else " X"
        print(f"{i:2} {got[i]:08x} | {want[i]:08x}{mark}")
print(f"{same}/{len(want)}" + ("  >>> EXACT <<<" if same == len(want) else ""))
