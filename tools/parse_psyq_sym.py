#!/usr/bin/env python3
"""
Parse a Psy-Q (SN Systems) .SYM debug-symbol file and emit a structured census.

Binary format mirrored exactly from lab313ru/ghidra_psx_ldr ImportPSX_SYM.java:

  Header (8 bytes): "MND\\x01" + 4-byte target-unit (ignored)
  Records, each: u32 address, u8 tag, then tag-specific payload.

  tag 0x01/0x02  symbol            : pascal name                (addressed label)
  tag 0x80       SLD inc           : -
  tag 0x82       SLD inc u8        : u8
  tag 0x84       SLD inc u16       : u16
  tag 0x86       SLD set line u32  : u32
  tag 0x88       SLD set file+line : u32 line, pascal file
  tag 0x8A       SLD end           : -
  tag 0x8C       function start    : u16 fp, u32 fsize, u16 retreg, u32 mask,
                                     u32 maskoffs, u32 line, pascal file, pascal name
  tag 0x8E       function end      : u32 endline   (record address = function end addr)
  tag 0x90       block start       : u32 line
  tag 0x92       block end         : u32 line
  tag 0x94       definition        : u16 class, u16 type, u32 size, pascal name
  tag 0x96       definition w/dims : u16 class, u16 type, u32 size, u16 dimCount,
                                     u32[dimCount], pascal structtag, pascal name

Pascal string = 1 length byte + that many ASCII chars (no terminator).

Usage:  python parse_psyq_sym.py <file.SYM> [--json out.json]
Prints a census summary to stdout; optional JSON dump of the raw parse.
"""
import sys
import os
import struct
import json
from collections import defaultdict, Counter

# Psy-Q C compiler base types (type & 0xF)
BASE_TYPE = {
    0: "null", 1: "void", 2: "char", 3: "short", 4: "int", 5: "long",
    6: "float", 7: "double", 8: "struct", 9: "union", 10: "enum",
    11: "moe", 12: "uchar", 13: "ushort", 14: "uint", 15: "ulong",
}


class Reader:
    def __init__(self, data):
        self.d = data
        self.p = 0

    def eof(self):
        return self.p >= len(self.d)

    def u8(self):
        v = self.d[self.p]
        self.p += 1
        return v

    def u16(self):
        v = struct.unpack_from("<H", self.d, self.p)[0]
        self.p += 2
        return v

    def u32(self):
        v = struct.unpack_from("<I", self.d, self.p)[0]
        self.p += 4
        return v

    def pstr(self):
        n = self.u8()
        s = self.d[self.p:self.p + n]
        self.p += n
        return s.decode("ascii", "replace")


def parse(data):
    r = Reader(data)
    sig = r.d[0:4]
    if sig != b"MND\x01":
        raise ValueError(f"bad signature {sig!r}, not a Psy-Q .SYM")
    r.p = 8  # skip magic + target-unit

    symbols = []       # (addr, name)  tags 0x01/0x02
    funcs = []         # dict: addr,name,file,line,end,size
    defs = []          # dict: addr,cls,type,size,name
    sld_files = set()  # source files seen via SLD (0x88)
    tag_counts = Counter()
    sld_line_records = 0

    cur_func = None
    while not r.eof():
        # a trailing partial record (<5 bytes) means clean EOF
        if len(data) - r.p < 5:
            break
        addr = r.u32()
        tag = r.u8()
        tag_counts[tag] += 1

        if tag in (0x01, 0x02) or (0x03 <= tag <= 0x7F):
            symbols.append((addr, r.pstr()))
        elif tag == 0x80:
            sld_line_records += 1
        elif tag == 0x82:
            r.u8(); sld_line_records += 1
        elif tag == 0x84:
            r.u16(); sld_line_records += 1
        elif tag == 0x86:
            r.u32(); sld_line_records += 1
        elif tag == 0x88:
            r.u32(); f = r.pstr(); sld_files.add(f); sld_line_records += 1
        elif tag == 0x8A:
            pass
        elif tag == 0x8C:
            fp = r.u16(); fsize = r.u32(); retreg = r.u16()
            mask = r.u32(); maskoffs = r.u32(); line = r.u32()
            file = r.pstr(); name = r.pstr()
            cur_func = {"addr": addr, "name": name, "file": file,
                        "line": line, "frame": fsize, "end": None, "size": None}
            funcs.append(cur_func)
        elif tag == 0x8E:
            r.u32()  # end line
            if cur_func is not None and cur_func["end"] is None:
                cur_func["end"] = addr
                cur_func["size"] = addr - cur_func["addr"]
                cur_func = None
        elif tag == 0x90:
            r.u32()
        elif tag == 0x92:
            r.u32()
        elif tag == 0x94:
            cls = r.u16(); typ = r.u16(); size = r.u32(); name = r.pstr()
            defs.append({"addr": addr, "cls": cls, "type": typ, "size": size, "name": name})
        elif tag == 0x96:
            cls = r.u16(); typ = r.u16(); size = r.u32()
            dc = r.u16()
            dims = [r.u32() for _ in range(dc)]
            stag = r.pstr(); name = r.pstr()
            defs.append({"addr": addr, "cls": cls, "type": typ, "size": size,
                         "name": name, "dims": dims, "structtag": stag})
        else:
            raise ValueError(f"unsupported tag 0x{tag:02x} at offset {r.p-1}")

    return {
        "symbols": symbols,
        "funcs": funcs,
        "defs": defs,
        "sld_files": sorted(sld_files),
        "tag_counts": dict(tag_counts),
        "sld_line_records": sld_line_records,
    }


def norm_module(path):
    """Reduce a source-file path to a coarse module key = its containing dir."""
    p = path.replace("\\", "/")
    parts = [x for x in p.split("/") if x]
    if len(parts) >= 2:
        return "/".join(parts[-2:-1]) or parts[-1]  # parent directory
    return parts[-1] if parts else path


def census(res):
    funcs = res["funcs"]
    symbols = res["symbols"]
    defs = res["defs"]

    # per source-file (from function-start records)
    by_file = defaultdict(lambda: {"funcs": 0, "bytes": 0})
    for f in funcs:
        k = f["file"] or "<none>"
        by_file[k]["funcs"] += 1
        if f["size"] and f["size"] > 0:
            by_file[k]["bytes"] += f["size"]

    # per coarse module (containing directory)
    by_mod = defaultdict(lambda: {"funcs": 0, "bytes": 0, "files": set()})
    for f in funcs:
        m = norm_module(f["file"] or "<none>")
        by_mod[m]["funcs"] += 1
        if f["size"] and f["size"] > 0:
            by_mod[m]["bytes"] += f["size"]
        by_mod[m]["files"].add(f["file"])

    # def base-type breakdown
    base_types = Counter()
    for d in defs:
        base_types[BASE_TYPE.get(d["type"] & 0xF, f"?{d['type']&0xF}")] += 1

    sized = [f["size"] for f in funcs if f["size"] and f["size"] > 0]
    total_code = sum(sized)

    return {
        "n_symbols": len(symbols),
        "n_funcs": len(funcs),
        "n_funcs_sized": len(sized),
        "total_func_bytes": total_code,
        "n_defs": len(defs),
        "n_source_files": len({f["file"] for f in funcs if f["file"]}),
        "sld_line_records": res["sld_line_records"],
        "by_file": {k: v for k, v in by_file.items()},
        "by_mod": {k: {"funcs": v["funcs"], "bytes": v["bytes"],
                       "nfiles": len(v["files"])} for k, v in by_mod.items()},
        "base_types": dict(base_types),
    }


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    path = sys.argv[1]
    with open(path, "rb") as fh:
        data = fh.read()
    res = parse(data)
    c = census(res)

    full_debug = (c["n_funcs"] > 0 and c["n_defs"] > 0 and c["sld_line_records"] > 0)
    print(f"=== Psy-Q .SYM census: {os.path.basename(path)} ({len(data):,} bytes) ===")
    print(f"debug richness   : {'FULL (functions + C types + source line info)' if full_debug else 'PARTIAL/PUBLIC-ONLY'}")
    print(f"addressed symbols: {c['n_symbols']:,}   (tags 0x01/0x02)")
    print(f"function records : {c['n_funcs']:,}  ({c['n_funcs_sized']:,} with a size)")
    print(f"  total code bytes (sum of sized funcs): {c['total_func_bytes']:,}")
    print(f"C type definitions: {c['n_defs']:,}")
    print(f"source files      : {c['n_source_files']:,}")
    print(f"SLD line records  : {c['sld_line_records']:,}")
    print(f"raw tag counts    : {dict(sorted(res['tag_counts'].items()))}")

    print("\n--- top 30 modules (containing dir) by function count ---")
    mods = sorted(c["by_mod"].items(), key=lambda kv: -kv[1]["funcs"])
    print(f"{'module':<34}{'funcs':>7}{'kbytes':>9}{'files':>7}")
    for m, v in mods[:30]:
        print(f"{m[:33]:<34}{v['funcs']:>7}{v['bytes']/1024:>9.1f}{v['nfiles']:>7}")

    print("\n--- def base-type breakdown ---")
    for t, n in sorted(c["base_types"].items(), key=lambda kv: -kv[1]):
        print(f"  {t:<10}{n:>7}")

    # JSON dump
    outjson = None
    if "--json" in sys.argv:
        outjson = sys.argv[sys.argv.index("--json") + 1]
    else:
        outjson = os.path.join("build", os.path.splitext(os.path.basename(path))[0] + "_sym.json")
    os.makedirs(os.path.dirname(outjson), exist_ok=True)
    with open(outjson, "w") as fh:
        json.dump({"census": c,
                   "funcs": res["funcs"],
                   "symbols": [{"addr": a, "name": n} for a, n in res["symbols"]],
                   "sld_files": res["sld_files"]}, fh, indent=1)
    print(f"\nwrote {outjson}")


if __name__ == "__main__":
    main()
