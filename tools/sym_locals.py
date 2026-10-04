#!/usr/bin/env python3
"""
Dump one function's debug info from the THPS2 demo's Psy-Q MAIN.SYM: parameters, nested blocks,
and every local with its C type, storage class and home (register or stack offset), in the order
the compiler emitted them (which is declaration order within each block).

  python tools/sym_locals.py <name-substring> [--sym extern/demo/PROSKATE/MAIN.SYM] [--lines]

Useful for matching: the declaration order, the block a variable lives in, its exact type and
the register cc1 gave it are all choices the matching C has to reproduce. Register homes are the
demo build's, so they're a strong hint for retail functions that are the same size.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
from parse_psyq_sym import Reader, BASE_TYPE  # noqa: E402

CLASS = {1: "auto", 2: "extern", 3: "static", 4: "reg", 6: "label", 8: "member", 9: "arg",
         10: "structtag", 11: "unionmember", 12: "uniontag", 13: "typedef", 15: "enumtag",
         16: "enummember", 17: "regparm", 18: "bitfield", 100: "block", 101: "func", 102: "eos"}
REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6",
       "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp",
       "fp", "ra"]


def ctype(typ, tag, dims):
    """COFF type word -> C-ish string: base type in the low 4 bits, then 2-bit derived types."""
    base = tag if tag and (typ & 0xF) in (8, 9, 10) else BASE_TYPE.get(typ & 0xF, "?")
    s, d, di = base, typ >> 4, list(dims or [])
    suffix = ""
    while d:
        k = d & 3
        if k == 1: s += "*"
        elif k == 2: suffix += "()"
        elif k == 3: suffix += f"[{di.pop(0) if di else ''}]"
        d >>= 2
    return s + suffix


def records(sym):
    """Yield (addr, tag, cls, typ, size, dims, stag, name) for every definition record."""
    r = Reader(open(sym, "rb").read()); r.p = 8
    while len(r.d) - r.p >= 5:
        addr, tag = r.u32(), r.u8()
        if tag in (0x01, 0x02) or 0x03 <= tag <= 0x7F: r.pstr()
        elif tag == 0x82: r.u8()
        elif tag == 0x84: r.u16()
        elif tag in (0x86, 0x8E, 0x90, 0x92): r.u32()
        elif tag == 0x88: r.u32(); r.pstr()
        elif tag == 0x8C: r.u16(); r.u32(); r.u16(); r.u32(); r.u32(); r.u32(); r.pstr(); r.pstr()
        elif tag in (0x94, 0x96):
            cls, typ, size = r.u16(), r.u16(), r.u32()
            dims, stag = [], ""
            if tag == 0x96: dims = [r.u32() for _ in range(r.u16())]; stag = r.pstr()
            yield addr, tag, cls, typ, size, dims, stag, r.pstr()


def dump_struct(sym, want):
    """--struct NAME: print the (first) struct/union definition with that exact tag, as C."""
    show = False
    for addr, tag, cls, typ, size, dims, stag, name in records(sym):
        if cls in (10, 12) and name == want and not show:
            show = True
            print(f"{'struct' if cls == 10 else 'union'} {name} {{  /* size {size:#x} */")
        elif show and cls in (8, 11, 18):
            bits = f" : {size}" if cls == 18 else ""
            print(f"  /* {addr:#05x} */ {ctype(typ, stag, dims):20} {name}{bits};")
        elif show and cls == 102:
            print("};"); return
    if not show: print(f"no struct {want!r}")


def dump_lines(sym, want):
    """--lines: the source line that starts at each word of the function (SLD records), so the
    retail listing (same code) can be split into the original statements."""
    r = Reader(open(sym, "rb").read()); r.p = 8
    sld, funcs, line = [], [], 0
    while len(r.d) - r.p >= 5:
        addr, tag = r.u32(), r.u8()
        if tag in (0x01, 0x02) or 0x03 <= tag <= 0x7F: r.pstr(); continue
        if tag == 0x80: line += 1
        elif tag == 0x82: line += r.u8()
        elif tag == 0x84: line += r.u16()
        elif tag == 0x86: line = r.u32()
        elif tag == 0x88: line = r.u32(); r.pstr()
        elif tag == 0x8A: continue
        elif tag == 0x8C:
            r.u16(); r.u32(); r.u16(); r.u32(); r.u32(); r.u32(); r.pstr(); funcs.append([addr, r.pstr(), None]); continue
        elif tag == 0x8E:
            r.u32()
            if funcs and funcs[-1][2] is None: funcs[-1][2] = addr
            continue
        elif tag in (0x90, 0x92): r.u32(); continue
        elif tag in (0x94, 0x96):
            r.u16(); r.u16(); r.u32()
            if tag == 0x96: [r.u32() for _ in range(r.u16())]; r.pstr()
            r.pstr(); continue
        else: raise ValueError(f"tag 0x{tag:02x}")
        sld.append((addr, line))
    for start, name, end in funcs:
        if want not in name: continue
        print(f"{name} @0x{start:08x}: source line starting at each word")
        first = None
        for addr, ln in sld:
            if start <= addr < (end or start):
                first = first or ln
                print(f"  w{(addr - start) // 4:<4} line {ln:5}  (+{ln - first})")
        return
    print(f"no function matching {want!r}")


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        print(__doc__); sys.exit(1)
    want = args[0]
    root = os.path.join(os.path.dirname(__file__), "..")
    sym = os.path.join(root, "extern", "demo", "PROSKATE", "MAIN.SYM")
    if "--sym" in sys.argv: sym = sys.argv[sys.argv.index("--sym") + 1]
    show_lines = "--lines" in sys.argv
    if "--struct" in sys.argv:
        return dump_struct(sym, want)
    if show_lines:
        return dump_lines(sym, want)
    r = Reader(open(sym, "rb").read()); r.p = 8
    inside, depth, line, found = False, 0, 0, 0
    while len(r.d) - r.p >= 5:
        addr, tag = r.u32(), r.u8()
        if tag in (0x01, 0x02) or 0x03 <= tag <= 0x7F: r.pstr(); continue
        if tag == 0x80: line += 1; ev = None
        elif tag == 0x82: line += r.u8(); ev = None
        elif tag == 0x84: line += r.u16(); ev = None
        elif tag == 0x86: line = r.u32(); ev = None
        elif tag == 0x88: line = r.u32(); r.pstr(); ev = None
        elif tag == 0x8A: ev = None
        elif tag == 0x8C:
            fp, fsize, retreg = r.u16(), r.u32(), r.u16()
            mask, maskoffs, fline = r.u32(), r.u32(), r.u32()
            file, name = r.pstr(), r.pstr()
            inside = want in name
            if inside:
                found += 1; depth = 1; line = fline
                saved = [REG[i] for i in range(32) if mask >> i & 1]
                print(f"{name} @0x{addr:08x}  {file}:{fline}")
                print(f"  frame {fsize} (fp={REG[fp]}), saves {' '.join(saved)} at {maskoffs:#x}")
            continue
        elif tag == 0x8E:
            end = r.u32()
            if inside: print(f"}} end @0x{addr:08x} line {end}\n")
            inside = False; continue
        elif tag in (0x90, 0x92):
            bl = r.u32()
            if inside:
                if tag == 0x90: print(f"{'  ' * depth}{{ block @0x{addr:08x} line {bl}"); depth += 1
                else: depth -= 1; print(f"{'  ' * depth}}} @0x{addr:08x} line {bl}")
            continue
        elif tag in (0x94, 0x96):
            cls, typ, size = r.u16(), r.u16(), r.u32()
            dims, stag = [], ""
            if tag == 0x96:
                dims = [r.u32() for _ in range(r.u16())]; stag = r.pstr()
            name = r.pstr()
            if inside and cls not in (8, 10, 11, 12, 13, 15, 16, 102):
                c = CLASS.get(cls, str(cls))
                home = (REG[addr] if addr < 32 else f"r{addr}") if cls in (4, 17) else \
                       f"sp+{addr:#x}" if cls in (1, 9) else f"0x{addr:08x}"
                print(f"{'  ' * depth}{c:8} {ctype(typ, stag, dims):28} {name:20} {home}")
            continue
        else:
            raise ValueError(f"tag 0x{tag:02x}")
        if inside and show_lines and tag != 0x8A:
            print(f"{'  ' * depth}  line {line} @0x{addr:08x}")
    if not found: print(f"no function matching {want!r}")


if __name__ == "__main__":
    main()
