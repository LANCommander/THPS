#!/usr/bin/env python3
"""Review the names that callers wrote into .syms.json for functions still FUN_ in functions.tsv.

For each candidate: is it a typed function in the demo MAIN.SYM, how similar is its opcode sequence
to the retail function, is the name already used at another address? PROMOTE = SYM function,
opcode similarity >= 0.75, the only candidate, name unused. Writes decomp/caller_names_review.tsv.

    python tools/review_caller_names.py
"""
import json,glob,re,collections,difflib,sys
sys.path.insert(0,'tools'); from fuzzy_twins import words,opkey,DEMO_EXE,DEMO_TEXT,RETAIL_EXE,RETAIL_TEXT
sym=json.load(open('build/MAIN_sym.json'))
dfun={f['name']:f for f in sym['funcs']}
dlab={s['name'] for s in sym['symbols']}
db=open(DEMO_EXE,'rb').read(); rb=open(RETAIL_EXE,'rb').read()
rows=[l.rstrip('\n').split('\t') for l in open('decomp/functions.tsv') if l.startswith('0x')]
used=collections.Counter(r[2] for r in rows)
cands=collections.defaultdict(collections.Counter)
for f in glob.glob('decomp/src/**/*.syms.json',recursive=True):
  for k,v in json.load(open(f)).items():
    if isinstance(v,str) and v.startswith('0x') and not k.startswith(('FUN_','DAT_','.','gp','_vt','LAB_','D_')):
      cands[int(v,16)][k]+=1
out=[]
for r in rows:
  a=int(r[0],16); sz=int(r[1])
  if not r[2].startswith('FUN_') or a not in cands: continue
  rw=[opkey(w) for w in words(rb,RETAIL_TEXT,a,sz)]
  for n,c in cands[a].items():
    if n in dfun:
      d=dfun[n]; dw=[opkey(w) for w in words(db,DEMO_TEXT,d['addr'],d['size'])]
      sim=difflib.SequenceMatcher(None,rw,dw,autojunk=False).ratio(); src='SYM'; dsz=d['size']
    else: sim=None; src='label' if n in dlab else 'none'; dsz=0
    conflict=used[n]>0
    if src=='SYM' and sim>=0.75 and not conflict and len(cands[a])==1: v='PROMOTE'
    elif src=='none': v='NOT-IN-SYM'
    else: v='REVIEW'
    out.append((v,r[0],sz,n,dsz,'' if sim is None else '%.2f'%sim,c,len(cands[a]),'dup-name' if conflict else ''))
out.sort()
with open('decomp/caller_names_review.tsv','w') as f:
  f.write('# verdict\tretail\tsize\tcandidate\tdemo_size\topcode_sim\tsyms_refs\tcandidates_at_addr\tnote\n')
  for o in out: f.write('\t'.join(map(str,o))+'\n')
print(collections.Counter(o[0] for o in out), len({o[1] for o in out}),'addrs')
for o in out:
  if o[0]!='PROMOTE': print(*o)
