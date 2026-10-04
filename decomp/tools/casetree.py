"""Emulate GCC 2.8's compare-tree switch lowering (stmt.c: group_case_nodes, balance_case_nodes,
emit_case_nodes) and compare it with a retail function's tree.

A switch that isn't dense enough for a jump table becomes a balanced binary tree of compares, and
the tree's shape depends on the exact set of case *nodes*: maximal runs of consecutive values that
share a label. Empty groups and `return x;` groups are invisible in the bodies but still shape the
tree. This tool predicts the compare sequence for a proposed case set so the set can be fitted.

    node tools/dis.mjs <addr> <size> > build/f.dis
    python tools/casetree.py build/f.dis <firstTreeWord> <endWord> <spec.py>
    python tools/casetree.py --s <cc1 output .s> <spec.py>     # check the model on your own build

<spec.py> defines CASES = [(lo, hi, label), ...] and optionally SAME(label) -> class. Labels are
strings; consecutive nodes merge when they have the same label, or when both labels start with
"brk" (plain `break;` bodies are simple jumps to one place, which group_case_nodes also merges).
SAME maps labels whose code is identical after jump threading (the default, `break;` groups and
`return x;` groups usually) to one class: the jump optimizer deletes a compare whose target is
in the same class as the jump that follows it, so such compares vanish from the output. A case
group that shares the `default:` label is therefore invisible except through the tree's balance.
The index is an int (a promoted ushort/uchar), so its lowest value is never treated as bounded.

To fit a case set: give every distinct body its own label, then search over optional empty groups
in the value gaps (see SkipCommand's notes in README) until the predicted sequence equals retail's.

Compares are printed as eq K (addiu+beq), ge K (slti K; beq zero) and lt K (slti K; bne zero).
"""
import re, sys

INT_MIN = -(1 << 31)


class Node:
    def __init__(s, lo, hi, label):
        s.lo, s.hi, s.label = lo, hi, label
        s.left = s.right = s.parent = None


def group(cases):
    cases = sorted(cases)
    out = []
    for lo, hi, lab in cases:
        if out and out[-1].hi + 1 == lo and (out[-1].label == lab or (out[-1].label.startswith('brk') and lab.startswith('brk'))):
            out[-1].hi = hi
        else:
            out.append(Node(lo, hi, lab))
    for a, b in zip(out, out[1:]):
        a.right = b
    return out[0] if out else None


def balance(head, parent):
    np = head
    if not np:
        return None
    i = ranges = 0
    while np:
        if np.lo != np.hi:
            ranges += 1
        i += 1
        np = np.right
    if i > 2:
        # walk to the split point
        left = head
        if i == 3:
            prev, cur = head, head.right
        else:
            i = (i + ranges + 1) // 2
            prev, cur = None, head
            while True:
                if cur.lo != cur.hi:
                    i -= 1
                i -= 1
                if i <= 0:
                    break
                prev, cur = cur, cur.right
        np = cur
        if prev:
            prev.right = None
        np.parent = parent
        np.left = left if prev else None
        np.left = balance(np.left, np) if np.left else None
        np.right = balance(np.right, np)
        return np
    np = head
    np.parent = parent
    while np.right:
        np.right.parent = np
        np = np.right
    return head


def has_low(n):
    if n.lo == INT_MIN:
        return True
    if n.left:
        return False
    p = n.parent
    while p:
        if p.hi == n.lo - 1:
            return True
        p = p.parent
    return False


def has_high(n):
    if n.right:
        return False
    p = n.parent
    while p:
        if p.lo == n.hi + 1:
            return True
        p = p.parent
    return False


def bounded(n):
    return has_low(n) and has_high(n)


def emit(n, out):
    """Appends (op, K, target) in code order. target is a label or 'default' or 'T<n>'."""
    if bounded(n):
        out.append(('j', None, n.label))
        return
    if n.lo == n.hi:
        out.append(('eq', n.lo, n.label))
        if n.right and n.left:
            if bounded(n.right):
                out.append(('ge', n.hi + 1, n.right.label))
                emit(n.left, out)
            elif bounded(n.left):
                out.append(('lt', n.hi, n.left.label))
                emit(n.right, out)
            else:
                t = 'T%d' % len(out)
                out.append(('ge', n.hi + 1, t))
                emit(n.left, out)
                out.append(('j', None, 'default'))
                out.append(('label', None, t))
                emit(n.right, out)
        elif n.right:
            r = n.right
            if r.right or r.left or r.lo != r.hi:
                if not has_low(n):
                    out.append(('lt', n.hi, 'default'))
                emit(r, out)
            else:
                out.append(('eq', r.lo, r.label))
        elif n.left:
            l = n.left
            if l.right or l.left or l.lo != l.hi:
                if not has_high(n):
                    out.append(('ge', n.hi + 1, 'default'))
                emit(l, out)
            else:
                out.append(('eq', l.lo, l.label))
    else:
        if n.right and n.left:
            t = None
            if bounded(n.right):
                out.append(('ge', n.hi + 1, n.right.label))
            else:
                t = 'T%d' % len(out)
                out.append(('ge', n.hi + 1, t))
            out.append(('ge', n.lo, n.label))
            emit(n.left, out)
            if t:
                out.append(('j', None, 'default'))
                out.append(('label', None, t))
                emit(n.right, out)
        elif n.right:
            if not has_low(n):
                out.append(('lt', n.lo, 'default'))
            out.append(('lt', n.hi + 1, n.label))
            emit(n.right, out)
        elif n.left:
            if not has_high(n):
                out.append(('ge', n.hi + 1, 'default'))
            out.append(('ge', n.lo, n.label))
            emit(n.left, out)
        else:
            if not has_high(n):
                out.append(('ge', n.hi + 1, 'default'))
            if not has_low(n):
                out.append(('lt', n.lo, 'default'))
            out.append(('j', None, n.label))


def predict(cases, same=lambda t: t):
    """same(label) maps a target to its equivalence class after jump threading (e.g. every label
    whose body is just `return x;` and the default). A conditional branch immediately followed
    by a jump to the same class is deleted by the jump optimizer, so it doesn't appear."""
    root = balance(group(cases), None)
    out = []
    emit(root, out)
    out.append(('j', None, 'default'))
    cls = lambda t: same(t) if not t.startswith('T') else t
    changed = True
    while changed:
        changed = False
        for i in range(len(out) - 1):
            if out[i][0] in ('eq', 'ge', 'lt') and out[i + 1][0] == 'j' and cls(out[i][2]) == cls(out[i + 1][2]):
                del out[i]
                changed = True
                break
    return [(op, k) for op, k, _ in out if op in ('eq', 'ge', 'lt')]


def retail_compares(dis_path, start, end):
    """Extracts eq/ge/lt compares (on the switch index) from a dis.mjs listing, words [start, end)."""
    ins = {}
    for l in open(dis_path).read().splitlines()[1:]:
        m = re.match(r'\s*(?:L\d+:)?\s*(\d+) [0-9a-f]{8}\s+(\S+)\s*(.*?)\s*(;.*)?$', l)
        if m:
            ins[int(m.group(1))] = (m.group(2), [x.strip() for x in m.group(3).split(',')] if m.group(3) else [])
    out = []
    w = start
    while w < end:
        op, a = ins[w]
        if op == 'slti':
            k = int(a[2])
            # the branch is the next word that tests a[0]
            for j in range(w + 1, w + 3):
                bop, ba = ins[j]
                if bop in ('beq', 'bne') and ba[0] == a[0] and ba[1] == 'zero':
                    out.append(('ge' if bop == 'beq' else 'lt', k))
                    break
        elif op in ('addiu', 'ori') and a[1] == 'zero':
            k = int(a[2])
            j = w + 1
            if ins[j][0] in ('beq', 'bne') and a[0] in ins[j][1][:2] and 'zero' not in ins[j][1][:2]:
                out.append(('eq', k))
        w += 1
    return out


def s_compares(path):
    """Same, from a cc1 .s file (the whole function: run it on a one-function source)."""
    out, pend = [], None
    for l in open(path):
        p = l.split('#')[0].split()
        if not p:
            continue
        op, a = p[0], ''.join(p[1:]).split(',')
        if op == 'slt' and len(a) == 3 and a[2].lstrip('-').isdigit():
            pend = ('slt', a[0], int(a[2]))
        elif op == 'li' and len(a) == 2:
            pend = ('li', a[0], int(a[1], 0))
        elif op in ('bltz', 'bgez'):
            out.append(('lt' if op == 'bltz' else 'ge', 0)); pend = None
        elif op in ('beq', 'bne') and pend:
            if pend[0] == 'slt' and a[0] == pend[1] and a[1] == '$0':
                out.append(('ge' if op == 'beq' else 'lt', pend[2]))
            elif pend[0] == 'li' and pend[1] in a[:2] and '$0' not in a[:2]:
                out.append(('eq', pend[2]))
            pend = None
        elif op not in ('.set', 'nop'):
            pend = pend if op.startswith('.') else None
    return out


if __name__ == '__main__' and sys.argv[1] == '--s':
    env = {}
    exec(open(sys.argv[3]).read(), env)
    want = s_compares(sys.argv[2])
    got = predict(env['CASES'], env.get('SAME', lambda t: t))
    print('cc1    ', ' '.join(f'{o}{k}' for o, k in want))
    print('predict', ' '.join(f'{o}{k}' for o, k in got))
    print('MATCH' if want == got else 'differ')
    sys.exit()

if __name__ == '__main__':
    dis, start, end, spec = sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), sys.argv[4]
    env = {}
    exec(open(spec).read(), env)
    want = retail_compares(dis, start, end)
    got = predict(env['CASES'], env.get('SAME', lambda t: t))
    print('retail ', ' '.join(f'{o}{k}' for o, k in want))
    print('predict', ' '.join(f'{o}{k}' for o, k in got))
    print('MATCH' if want == got else 'differ')
