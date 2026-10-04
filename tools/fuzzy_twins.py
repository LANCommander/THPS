#!/usr/bin/env python3
"""Find the closest THPS2-demo function for each retail function that has no exact twin.

match_functions.py only pairs byte-identical (modulo relocation) functions. Many retail functions
are earlier versions of a demo function: same callees, same shape, a few statements different. The
demo's MAIN.SYM still describes their locals, types and statement order, so finding the pairing is
worth a lot on big functions.

Two signals, both relocation-proof:
  * opcode shingles: each instruction reduced to its opcode (plus funct/rt/rs selector for
    SPECIAL/REGIMM/COP), then 5-grams; Jaccard similarity via an inverted index.
  * callee names: jal targets named through the demo SYM (demo side) and the ported exact-twin
    names (retail side); Jaccard over the named callees.

Writes build/fuzzy_twins.tsv (best candidate per retail function not yet in decomp/matched.tsv) and prints the
largest functions with a plausible twin.

    python tools/fuzzy_twins.py [--min-size 200] [--top 60]
"""
import json, struct, sys, collections

DEMO_EXE = "extern/demo/PROSKATE.EXE"
DEMO_TEXT = 0x80018000
RETAIL_EXE = "extern/thps1_retail/SLUS_008.60"
RETAIL_TEXT = 0x80010000
HDR = 0x800
N = 5


def words(buf, base, addr, size):
    o = addr - base + HDR
    return list(struct.unpack('<%dI' % (size // 4), buf[o:o + size // 4 * 4]))


def opkey(w):
    op = w >> 26
    if op == 0:
        return (0, w & 0x3f)
    if op == 1:
        return (1, (w >> 16) & 0x1f)
    if op in (0x10, 0x12):
        return (op, (w >> 21) & 0x1f, w & 0x3f if (w >> 25) & 1 else 0)
    return (op,)


def shingles(ws):
    ks = [opkey(w) for w in ws if w != 0]
    return {hash(tuple(ks[i:i + N])) for i in range(max(0, len(ks) - N + 1))}


def callees(ws, names):
    out = []
    for w in ws:
        if w >> 26 == 3:
            t = ((w & 0x3ffffff) << 2) | 0x80000000
            n = names.get(t)
            if n:
                out.append(n)
    return out


def main():
    min_size = 200
    top = 60
    a = sys.argv[1:]
    if '--min-size' in a:
        min_size = int(a[a.index('--min-size') + 1])
    if '--top' in a:
        top = int(a[a.index('--top') + 1])

    sym = json.load(open('build/MAIN_sym.json'))
    demo = [(f['addr'], f['size'], f['name'], f['file'].split('\\')[-1]) for f in sym['funcs'] if f['size'] >= 8]
    dbuf = open(DEMO_EXE, 'rb').read()
    rbuf = open(RETAIL_EXE, 'rb').read()
    demo_names = {d[0]: d[2] for d in demo}

    retail = []
    for l in open('decomp/functions.tsv'):
        if l.startswith('#') or not l.strip():
            continue
        p = l.rstrip('\n').split('\t')
        retail.append((int(p[0], 16), int(p[1]), p[2]))
    rnames = {}
    for l in open('build/retail_names.tsv'):
        p = l.rstrip('\n').split('\t')
        if len(p) >= 4 and p[2] == 'F':
            rnames.setdefault(int(p[0], 16), p[3])
    exact = {json.dumps(m['retail_addr']) for m in json.load(open('build/matches.json'))['exact_matches']}
    exact_demo = {m['name'] for m in json.load(open('build/matches.json'))['exact_matches']}
    done = {int(l.split('	')[1], 16) for l in open('decomp/matched.tsv') if l.strip() and not l.startswith('#')}

    # demo index
    dsh, dcal = {}, {}
    inv = collections.defaultdict(list)
    for addr, size, name, f in demo:
        ws = words(dbuf, DEMO_TEXT, addr, size)
        s = shingles(ws)
        dsh[name] = s
        dcal[name] = set(callees(ws, demo_names))
        for h in s:
            inv[h].append(name)
    common = {h for h, v in inv.items() if len(v) > 40}
    dinfo = {d[2]: d for d in demo}

    rows = []
    for addr, size, name in retail:
        if json.dumps(addr) in exact or addr in done or size < min_size:
            continue
        ws = words(rbuf, RETAIL_TEXT, addr, size)
        s = shingles(ws) - common
        if not s:
            continue
        cnt = collections.Counter()
        for h in s:
            for n in inv.get(h, ()):
                cnt[n] += 1
        cal = set(callees(ws, rnames))
        best = []
        for n, c in cnt.most_common(25):
            ds = dsh[n] - common
            jac = c / len(s | ds)
            dc = dcal[n]
            cj = len(cal & dc) / len(cal | dc) if (cal or dc) else 0.0
            best.append((0.6 * jac + 0.4 * cj, jac, cj, n))
        if not best:
            continue
        best.sort(reverse=True)
        sc, jac, cj, n = best[0]
        d = dinfo[n]
        rows.append((addr, size, name, n, d[1], d[3], sc, jac, cj, n in exact_demo))

    with open('build/fuzzy_twins.tsv', 'w') as f:
        f.write('# retail\tsize\tname\tdemo_twin\tdemo_size\tfile\tscore\tshingle_jacc\tcallee_jacc\tdemo_already_exact\n')
        for r in sorted(rows, key=lambda r: -r[6]):
            f.write('0x%08x\t%d\t%s\t%s\t%d\t%s\t%.3f\t%.3f\t%.3f\t%s\n' % (r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9]))
    good = [r for r in rows if r[6] >= 0.35]
    print(f'{len(rows)} unmatched retail functions >= {min_size} B scored; {len(good)} with score >= 0.35')
    for r in sorted(good, key=lambda r: -r[1])[:top]:
        print('0x%08x %5d %-14s -> %-48s %5d %-14s score %.2f (shingle %.2f, callee %.2f)%s' % (
            r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], ' [demo fn already exact elsewhere]' if r[9] else ''))


if __name__ == '__main__':
    main()
