"""Flag calls that pass more arguments than the callee reads.

m2c often shows extra call arguments that are just stale registers (a0-a3 left over from earlier
code). Passing them costs `addiu a0,...` setup that retail doesn't have, or moves a delay slot
(FUN_8005c97c: FUN_8006af64 takes no arguments). For each callee named in a source's syms.json,
this scans the callee's code and reports how many of a0-a3 it reads before writing them. Calls
in the source with more arguments than that are printed.

    python tools/argcheck.py [src ...]      (default: every source in nearmiss.tsv)
"""
import json, os, re, struct, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
RETAIL = os.path.join(ROOT, '..', 'extern', 'thps1_retail', 'SLUS_008.60')
BUF = open(RETAIL, 'rb').read()
TEXT, HDR = 0x80010000, 0x800


def word(addr):
    o = addr - TEXT + HDR
    return struct.unpack_from('<I', BUF, o)[0] if 0 <= o < len(BUF) - 4 else None


def regs(w):
    """(reads, writes) register sets for one MIPS I instruction (enough for a0-a3 tracking)."""
    op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
    if w == 0:
        return set(), set()
    if op == 0:
        fn = w & 63
        if fn in (0, 2, 3):                       # sll/srl/sra
            return {rt}, {rd}
        if fn in (8,):                            # jr
            return {rs}, set()
        if fn == 9:                               # jalr
            return {rs}, {rd}
        if fn in (0x10, 0x12):                    # mfhi/mflo
            return set(), {rd}
        if fn in (0x11, 0x13):                    # mthi/mtlo
            return {rs}, set()
        if fn in (0x18, 0x19, 0x1a, 0x1b):        # mult/div
            return {rs, rt}, set()
        return {rs, rt}, {rd}
    if op == 1:                                   # bltz/bgez...
        return {rs}, set()
    if op in (2, 3):                              # j/jal
        return set(), ({31} if op == 3 else set())
    if op in (4, 5):                              # beq/bne
        return {rs, rt}, set()
    if op in (6, 7):                              # blez/bgtz
        return {rs}, set()
    if 8 <= op <= 15:                             # immediate ALU, lui
        return ({rs} if op != 15 else set()), {rt}
    if 0x20 <= op <= 0x26:                        # loads
        return {rs}, {rt}
    if 0x28 <= op <= 0x2e:                        # stores
        return {rs, rt}, set()
    if op == 0x32:                                # lwc2
        return {rs}, set()
    if op == 0x3a:                                # swc2
        return {rs}, set()
    if op == 0x12:                                # cop2 mtc2/ctc2 read rt; mfc2/cfc2 write rt
        sub = rs
        return ({rt}, set()) if sub in (4, 6) else (set(), {rt})
    return set(), set()


def args_read(addr, limit=80):
    """Highest a-register index (0..3) read before being written, scanning straight-line-ish code
    (follows fall-through only; stops at the first jr/j)."""
    written, used = set(), set()
    for i in range(limit):
        w = word(addr + 4 * i)
        if w is None:
            break
        r, wr = regs(w)
        for a in (4, 5, 6, 7):
            if a in r and a not in written:
                used.add(a)
        written |= wr
        op = w >> 26
        if (op == 0 and (w & 63) == 8) or op == 2:
            # include the delay slot
            w2 = word(addr + 4 * (i + 1))
            if w2 is not None:
                r2, _ = regs(w2)
                for a in (4, 5, 6, 7):
                    if a in r2 and a not in written:
                        used.add(a)
            break
        if op == 3:      # a call clobbers a0-a3 for anything after it
            w2 = word(addr + 4 * (i + 1))
            if w2 is not None:
                r2, wr2 = regs(w2)
                for a in (4, 5, 6, 7):
                    if a in r2 and a not in written:
                        used.add(a)
                written |= wr2
            written |= {4, 5, 6, 7}
    return (max(used) - 3) if used else 0


def manifest():
    rows = []
    for l in open(os.path.join(ROOT, 'nearmiss.tsv')):
        if l.startswith('#') or not l.strip():
            continue
        rows.append(l.split('\t')[0])
    return rows


def check(src):
    path = os.path.join(ROOT, src)
    syms = os.path.splitext(path)[0] + '.syms.json'
    if not os.path.exists(syms):
        return
    sym = json.load(open(syms))
    text = open(path).read()
    for name, a in sym.items():
        if name in ('gp', '.rdata') or not isinstance(a, str):
            continue
        addr = int(a, 16)
        if not (0x80010000 <= addr < 0x80098000):
            continue
        base = name.split('__')[0] if '__F' in name else name
        n = args_read(addr)
        for m in re.finditer(r'\b' + re.escape(base) + r'\s*\(([^;{]*?)\)\s*;', text):
            inner = m.group(1).strip()
            if inner in ('', 'void') or '(' in inner and inner.count('(') != inner.count(')'):
                continue
            depth, cnt = 0, 1
            for ch in inner:
                if ch in '([':
                    depth += 1
                elif ch in ')]':
                    depth -= 1
                elif ch == ',' and depth == 0:
                    cnt += 1
            if cnt > n and n < 4:
                print(f'{src}: {base}(...{cnt} args) but {name} reads {n} (a0..a{n-1})')
                break


if __name__ == '__main__':
    for s in sys.argv[1:] or manifest():
        check(s)
