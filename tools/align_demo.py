#!/usr/bin/env python3
"""Line up a retail address range against the function order of demo source files, scoring each
retail function against every demo function in them (opcode-sequence similarity). A source file
keeps its function order, so a run of confident matches pins down the unnamed slots between them.

    python tools/align_demo.py 0x80027100 0x8002a100 BIT.CPP[,BIT2.CPP]
"""
import json,struct,difflib,sys
sys.path.insert(0,'tools'); from fuzzy_twins import opkey
sym=json.load(open('build/MAIN_sym.json'))
db=open('extern/demo/PROSKATE.EXE','rb').read(); rb=open('extern/thps1_retail/SLUS_008.60','rb').read()
def ops(b,base,a,n): return [opkey(x) for x in struct.unpack_from('<%dI'%(n//4),b,a-base+0x800)]
rows=[l.rstrip('\n').split('\t') for l in open('decomp/functions.tsv') if l.startswith('0x')]
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16); files=sys.argv[3].split(',')
dem=sorted([f for f in sym['funcs'] if f['file'].split(chr(92))[-1] in files],key=lambda f:f['addr'])
dops={f['name']:ops(db,0x80018000,f['addr'],f['size']) for f in dem}
print('--- demo order:',' | '.join(f"{f['name']}({f['size']})" for f in dem))
for r in rows:
  a=int(r[0],16)
  if not lo<=a<hi: continue
  ro=ops(rb,0x80010000,a,int(r[1]))
  sc=sorted(((difflib.SequenceMatcher(None,ro,dops[f['name']],autojunk=False).ratio(),f['name'],f['size']) for f in dem),reverse=True)[:2]
  print(f"{r[0]} {r[1]:>5} {r[2][:44]:44} best: "+'; '.join(f"{n}({s}) {x:.2f}" for x,n,s in sc))
