"""Opcode-level diff between a retail function and its (fuzzy) demo twin.

    python tools/twindiff.py <retailAddrHex> <demoMangledName>

Registers and immediates are ignored, so only real shape differences are printed: statements THPS1
lacks or adds, compared with the demo whose MAIN.SYM describes the source.
"""
import re, subprocess, sys, difflib, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load(args, env):
    out = subprocess.run(['node', 'tools/dis.mjs'] + args, capture_output=True, text=True, cwd=ROOT, env=env).stdout
    rows = []
    for l in out.splitlines()[1:]:
        m = re.match(r'\s*(?:L\d+:)?\s*(\d+) [0-9a-f]{8}\s+(\S+)\s*([^;]*)', l)
        if m:
            rows.append((int(m.group(1)), m.group(2), m.group(3).strip()))
    return rows


r = load([sys.argv[1]], dict(os.environ))
d = load([sys.argv[2]], dict(os.environ, DEMO='1'))
sm = difflib.SequenceMatcher(None, [x[1] for x in d], [x[1] for x in r], autojunk=False)
print(f'demo {len(d)} words, retail {len(r)} words, opcode similarity {sm.ratio():.3f}')
for op, a1, a2, b1, b2 in sm.get_opcodes():
    if op == 'equal':
        continue
    print(f'{op} demo {a1}-{a2} retail {b1}-{b2}')
    for i in range(a1, a2):
        print('   D %4d %s %s' % d[i])
    for i in range(b1, b2):
        print('   R %4d %s %s' % r[i])
