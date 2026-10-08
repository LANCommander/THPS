#!/usr/bin/env python3
"""Name retail call targets through exact demo twins: a twin pair has the same instruction stream,
so the k-th jal in each calls the same function. Collects the demo callee names per retail target
(votes, plus which twins voted) into build/callsite_names.json and lists the FUN_ targets, and the
named ones whose current name disagrees. One name with several votes is strong evidence; several
names at one target mean a shared helper (inherited operator delete, a base destructor).

    python tools/callsite_names.py
"""
import json,struct,collections,sys
sym=json.load(open('build/MAIN_sym.json'))
dnames={f['addr']:f['name'] for f in sym['funcs']}
for s in sym['symbols']: dnames.setdefault(s['addr'],s['name'])
db=open('extern/demo/PROSKATE.EXE','rb').read(); rb=open('extern/thps1_retail/SLUS_008.60','rb').read()
def w(buf,base,a,n): o=a-base+0x800; return struct.unpack_from('<%dI'%(n//4),buf,o)
def jals(ws): return [((x&0x3ffffff)<<2)|0x80000000 for x in ws if x>>26==3]
m=json.load(open('build/matches.json'))['exact_matches']
votes=collections.defaultdict(collections.Counter)
for e in m:
  if not e.get('retail_addr'): continue
  rj=jals(w(rb,0x80010000,e['retail_addr'],e['size'])); dj=jals(w(db,0x80018000,e['demo_addr'],e['size']))
  if len(rj)!=len(dj): continue
  for r,d in zip(rj,dj):
    if d in dnames: votes[r][(dnames[d],e['name'])]+=1
rows=[l.rstrip('\n').split('\t') for l in open('decomp/functions.tsv') if l.startswith('0x')]
out={}
for r in rows:
  a=int(r[0],16)
  if a in votes:
    names=collections.Counter()
    for (n,caller),c in votes[a].items(): names[n]+=c
    out[a]=(r[2],dict(names),sorted({c for (n,c) in votes[a]})[:3])
json.dump({hex(k):v for k,v in out.items()},open('build/callsite_names.json','w'),indent=1)
fun=[(hex(a),v) for a,v in out.items() if v[0].startswith('FUN_')]
bad=[(hex(a),v) for a,v in out.items() if not v[0].startswith('FUN_') and v[0] not in v[1]]
print('retail call targets named via twin call sites:',len(out),' of which FUN_:',len(fun),' named-but-disagree:',len(bad))
for x in fun: print('FUN',x)
for x in bad[:30]: print('DISAGREE',x)
