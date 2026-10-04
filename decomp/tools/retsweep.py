"""Try giving void callees a return value, one prototype at a time, in near-miss sources.

A call to a function that returns a value is a call_value: it sets v0, which changes local-alloc's
choices around the call even when the result is ignored. Several near-misses were exactly that
(CCar::AI with Trig_GetPosition, CMenu::Update with SFX_PlayX). For each source, every prototype
`void NAME(...);` is rewritten to `int NAME(...);` on its own and rematched; improvements are
reported and written back (greedily: each improvement is kept and the sweep restarts from it).

    python tools/retsweep.py [src ...]      (default: every source in nearmiss.tsv)
"""
import re, subprocess, sys, os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)


def manifest():
    rows = {}
    for l in open(os.path.join(ROOT, 'nearmiss.tsv')):
        if l.startswith('#') or not l.strip():
            continue
        p = l.rstrip('\n').split('\t')
        rows[p[0]] = (p[1], p[2], p[3])
    return rows


def score(src, addr, size, tool):
    base = src.rsplit('.', 1)[0]
    syms = base + '.syms.json'
    if tool == 'div':
        cmd = ['python', 'tools/match_div.py', src, addr, size] + ([syms] if os.path.exists(os.path.join(ROOT, syms)) else []) + ['-G8']
    elif tool == 'sym':
        cmd = ['node', 'tools/match_sym.mjs', src, addr, size, syms]
    else:
        cmd = ['node', 'tools/matchcc.mjs', src, addr, size, '-O2', '-G0']
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT)
    out = r.stdout.strip().splitlines()
    if not out:
        return -1, False
    m = re.match(r'(\d+)/(\d+)', out[-1])
    al = [l for l in out if l.startswith('aligned')]
    a = int(re.match(r'aligned (\d+)', al[0]).group(1)) if al else (int(m.group(1)) if m else -1)
    return a, 'EXACT' in out[-1]


PROTO = re.compile(r'^(\s*)void(\s+\**\s*)([A-Za-z_]\w*)\s*\(([^)]*)\)\s*;', re.M)


def sweep(src, addr, size, tool):
    path = os.path.join(ROOT, src)
    text = open(path).read()
    base, _ = score(src, addr, size, tool)
    best = (base, None)
    ext = '.' + src.rsplit('.', 1)[1]
    tmp = 'build/_retsweep_%d%s' % (os.getpid(), ext)
    syms_src = src.rsplit('.', 1)[0] + '.syms.json'
    syms_tmp = tmp.rsplit('.', 1)[0] + '.syms.json'
    if os.path.exists(os.path.join(ROOT, syms_src)):
        open(os.path.join(ROOT, syms_tmp), 'w').write(open(os.path.join(ROOT, syms_src)).read())
    improved = True
    while improved:                       # greedy: keep each improvement and sweep again from it
        improved = False
        for m in PROTO.finditer(text):
            variant = text[:m.start()] + m.group(1) + 'int' + m.group(2) + m.group(3) + '(' + m.group(4) + ');' + text[m.end():]
            open(os.path.join(ROOT, tmp), 'w').write(variant)
            s, exact = score(tmp, addr, size, tool)
            if s > best[0] or exact:
                print(f'  {src}: int {m.group(3)}() {best[0]} -> {s}{"  EXACT" if exact else ""}')
                best = (s, m.group(3))
                text = variant
                open(path, 'w').write(text)
                if exact:
                    return True
                improved = True
                break
    return False

if __name__ == '__main__':
    rows = manifest()
    srcs = sys.argv[1:] or list(rows)
    for s in srcs:
        if s not in rows:
            print('not in nearmiss.tsv:', s)
            continue
        addr, size, tool = rows[s]
        sweep(s, addr, size, tool.split()[0])
