#!/usr/bin/env python3
"""
Name retail globals (the decomp's DAT_xxxxxxxx placeholders) from the THPS2 demo's MAIN.SYM.

A demo twin has the same code as its retail function, so an aligned lui/addiu|load|store pair (or a
gp-relative access) in both reaches the same global. The demo SYM names the demo address; every
twin casts a vote for that name at the retail address, and a name is kept only when the votes agree.

  python tools/data_names.py        writes decomp/data_names.tsv, prints a census

Twins: the demo-named rows of decomp/functions.tsv, build/matches.json's exact matches and
build/fuzzy_twins.tsv, aligned by opcode (difflib) so twins of different sizes work too. A demo
address resolves to a typed SYM global (extern/static def record, with C type and size), else a bare
SYM label, else an offset inside a typed object (`Base_<hex offset>`, the offset taken from Base's
own retail address when that's known). Non-identifier names (vtables `_vt.`, `_GLOBAL_.`) are left out.
"""
import bisect
import collections
import difflib
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(__file__))
from fuzzy_twins import opkey  # noqa: E402
from sym_locals import records, ctype  # noqa: E402

ROOT = os.path.join(os.path.dirname(__file__), "..")
P = lambda *a: os.path.join(ROOT, *a)  # noqa: E731
DEMO_BASE, RETAIL_BASE = 0x80018000, 0x80010000
DEMO_GP, RETAIL_GP = 0x800E0140, 0x800D1080  # __SN_GP_BASE; retail's from the startup code
AGREE = 0.75          # share of a retail address's votes the winning demo address needs
MIN_ALIGN = 0.5       # share of the shorter twin covered by matching opcode blocks
MIN_BLOCK = 4         # matching run (words) a vote must sit in; shorter runs disagree ~20% of the time
IDENT = re.compile(r"^[A-Za-z_]\w*$")
SECTION = re.compile(r"^_+\w*?_(obj|objend|org|orgend|size)$|^__SN_")

sym = json.load(open(P("build", "MAIN_sym.json")))
demo = open(P("extern", "demo", "PROSKATE.EXE"), "rb").read()
retail = open(P("extern", "thps1_retail", "SLUS_008.60"), "rb").read()


def words(b, base, a, n):
    return struct.unpack_from(f"<{n // 4}I", b, a - base + 0x800)


def sx(i):
    return i - 0x10000 if i & 0x8000 else i


LOADSTORE = {32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46, 50, 58}   # incl. lwc2/swc2


def data_refs(w, gp):
    """word index -> absolute address for each %lo / gp-relative access (lui tracked linearly)."""
    hi, out = {}, {}
    for i, x in enumerate(w):
        op, rs, rt, rd = x >> 26, (x >> 21) & 31, (x >> 16) & 31, (x >> 11) & 31
        imm = x & 0xFFFF
        if op == 15:
            hi[rt] = imm << 16
            continue
        if op == 9 or op in LOADSTORE:
            if rs in hi:
                out[i] = (hi[rs] + sx(imm)) & 0xFFFFFFFF
            elif rs == 28:
                out[i] = (gp + sx(imm)) & 0xFFFFFFFF
        if op == 0:
            hi.pop(rd, None)
        elif op == 3:
            hi.pop(31, None)
        elif 8 <= op <= 14 or 32 <= op <= 38:     # ALU-immediate and loads write rt
            hi.pop(rt, None)
    return out


def twins():
    """{(retail addr, demo addr): (demo size, retail size)}; the alignment filter drops bad pairs."""
    by_name = {f["name"]: f for f in sym["funcs"]}
    out = {}
    for l in open(P("decomp", "functions.tsv"), encoding="utf-8"):
        if l.startswith("0x"):
            a, s, n = l.split("\t")[:3]
            if n in by_name:
                out[int(a, 16), by_name[n]["addr"]] = (by_name[n]["size"], int(s))
    for m in json.load(open(P("build", "matches.json")))["exact_matches"]:
        out.setdefault((m["retail_addr"], m["demo_addr"]), (m["size"], m["size"]))
    for l in open(P("build", "fuzzy_twins.tsv")):
        if l[0] != "#":
            r, rs, _, dname, ds = l.split("\t")[:5]
            if dname in by_name:
                out.setdefault((int(r, 16), by_name[dname]["addr"]), (int(ds), int(rs)))
    return out


def demo_globals():
    """Typed globals {addr: (name, ctype, size)}, struct layouts {tag: [(off, ctype, name)]}."""
    typed, structs, cur = {}, {}, None
    for addr, tag, cls, typ, size, dims, stag, name in records(P("extern", "demo", "PROSKATE", "MAIN.SYM")):
        if cls in (10, 12):
            cur = structs.setdefault(name, []) if name not in structs else None
        elif cls in (8, 11) and cur is not None:
            cur.append((addr, ctype(typ, stag, dims), name))
        elif cls == 102:
            cur = None
        elif cls in (2, 3) and addr >= 0x80000000 and (typ >> 4) & 3 != 2:
            ptr = (typ >> 4) & 3 == 1
            typed.setdefault(addr, (name, ctype(typ, stag, dims), 4 if ptr else size, stag))
    return typed, structs


def member_hint(structs, stag, typ, size, off):
    """'mScale' / '[3].mScale' for an offset into a struct (or array of one)."""
    lay = structs.get(stag)
    if not lay:
        return ""
    idx = ""
    if typ.endswith("]"):
        n = int(typ[typ.rindex("[") + 1:-1] or 0)
        if n:
            idx, off = f"[{off // (size // n)}]", off % (size // n)
    best = [m for m in lay if m[0] <= off]
    return f"{idx}.{best[-1][2]}+{off - best[-1][0]:#x}" if best else idx


def main():
    typed, structs = demo_globals()
    funcs = (min(f["addr"] for f in sym["funcs"]), max(f["end"] for f in sym["funcs"]))
    labels = {s["addr"]: s["name"] for s in sym["symbols"]
              if not funcs[0] <= s["addr"] < funcs[1] and not SECTION.match(s["name"])}
    tkeys = sorted(typed)

    votes = collections.defaultdict(collections.Counter)
    pairs = twins()
    used = 0
    for (ra, da), (ds, rs) in pairs.items():
        dw, rw = words(demo, DEMO_BASE, da, ds), words(retail, RETAIL_BASE, ra, rs)
        sm = difflib.SequenceMatcher(None, [opkey(x) for x in dw], [opkey(x) for x in rw], autojunk=False)
        blocks = sm.get_matching_blocks()
        if sum(b.size for b in blocks) < MIN_ALIGN * min(len(dw), len(rw)):
            continue
        used += 1
        dr, rr = data_refs(dw, DEMO_GP), data_refs(rw, RETAIL_GP)
        for a, b, n in blocks:
            for k in range(n if n >= MIN_BLOCK else 0):
                if a + k in dr and b + k in rr and 0x80000000 <= rr[b + k] < 0x80200000:
                    votes[rr[b + k]][dr[a + k]] += 1

    # winner per retail address
    win = {}
    for ra, c in votes.items():
        (da, n), tot = c.most_common(1)[0], sum(c.values())
        if n >= AGREE * tot:
            win[ra] = (da, n, tot)
    # demo address -> retail address, for exact globals (to rebase offsets)
    base_retail = collections.defaultdict(collections.Counter)
    for ra, (da, n, _) in win.items():
        base_retail[da][ra] += n

    rows, ambiguous, stray = [], sum(1 for ra in votes if ra not in win), 0
    for ra, (da, n, tot) in sorted(win.items()):
        rb = base_retail[da].most_common(1)[0][0]
        if (da in typed or da in labels) and ra == rb:
            name, typ = (typed[da][0], typed[da][1]) if da in typed else (labels[da], "")
            kind, note = "exact", ""
        elif da in typed or da in labels:
            # the global's best-supported retail address is elsewhere: this is an offset into it (a
            # retail %lo folding a member offset the demo adds later), or a stray misaligned vote
            off = ra - rb
            if da not in typed or not 0 < off < typed[da][2]:
                stray += 1
                continue
            name, typ, kind = f"{typed[da][0]}_{off:x}", typed[da][1], "offset"
            hint = member_hint(structs, typed[da][3], typed[da][1], typed[da][2], off)
            note = "; ".join(x for x in (f"{typed[da][0]}{hint}" if hint else "", "demo accesses the base") if x)
        else:
            i = bisect.bisect_right(tkeys, da) - 1
            if i < 0 or da - tkeys[i] >= typed[tkeys[i]][2]:
                continue
            b = tkeys[i]
            bname, btyp, bsize, bstag = typed[b]
            off = da - b
            if base_retail[b]:
                rb = base_retail[b].most_common(1)[0][0]
                note = "" if ra - rb == off else f"retail offset {ra - rb:#x} != demo {off:#x}"
                off = ra - rb
            else:
                note = "base not referenced in retail twins"
            if off < 0:
                continue
            name, typ, kind = f"{bname}_{off:x}", btyp, "offset"
            hint = member_hint(structs, bstag, btyp, bsize, da - b)
            note = "; ".join(x for x in (f"{bname}{hint}" if hint else "", note) if x)
        if IDENT.match(name):
            rows.append([ra, name, kind, n, tot, da, typ, note])

    # one name, one address: a clash (same-named statics, two retail copies) keeps neither
    count = collections.Counter(r[1] for r in rows)
    clash = sorted({r[1] for r in rows if count[r[1]] > 1})
    rows = [r for r in rows if count[r[1]] == 1]

    with open(P("decomp", "data_names.tsv"), "w", encoding="utf-8", newline="\n") as o:
        o.write("# Retail globals named from their THPS2-demo twins (tools/data_names.py; don't edit by hand).\n"
                "# votes = aligned twin accesses agreeing / all accesses seen. kind: exact = a demo SYM global or\n"
                "# label at the twin address; offset = <Base>_<hex offset> inside a typed demo object (note: member).\n"
                "# addr\tname\tkind\tvotes\tdemo_addr\tdemo_type\tnote\n")
        for ra, name, kind, n, tot, da, typ, note in rows:
            o.write(f"0x{ra:08x}\t{name}\t{kind}\t{n}/{tot}\t0x{da:08x}\t{typ}\t{note}\n")
    print(f"twins {len(pairs)} (aligned {used}); retail data addresses seen {len(votes)}, "
          f"ambiguous {ambiguous}, stray {stray}, named {len(rows)} "
          f"({sum(r[2] == 'exact' for r in rows)} exact, {sum(r[2] == 'offset' for r in rows)} offset); "
          f"name clashes dropped {len(clash)}: {' '.join(clash[:12])}{' ...' if len(clash) > 12 else ''}")


if __name__ == "__main__":
    main()
