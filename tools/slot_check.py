#!/usr/bin/env python3
"""Score proposed names: one "0xADDR demo_name" per line on stdin; prints retail size, demo size and
opcode-sequence similarity.

    printf "0x80043ae0 ShadowOn__5CBody
" | python tools/slot_check.py
"""
import json,struct,difflib,sys
sys.path.insert(0,'tools'); from fuzzy_twins import opkey
sym=json.load(open('build/MAIN_sym.json')); D={f['name']:f for f in sym['funcs']}
db=open('extern/demo/PROSKATE.EXE','rb').read(); rb=open('extern/thps1_retail/SLUS_008.60','rb').read()
sz={int(l.split('\t')[0],16):int(l.split('\t')[1]) for l in open('decomp/functions.tsv') if l.startswith('0x')}
def ops(b,base,a,n): return [opkey(x) for x in struct.unpack_from('<%dI'%(n//4),b,a-base+0x800)]
for l in sys.stdin:
  if not l.strip(): continue
  a,n=l.split(); a=int(a,16)
  if n not in D: print(hex(a),n,'NOT IN DEMO'); continue
  s=difflib.SequenceMatcher(None,ops(rb,0x80010000,a,sz[a]),ops(db,0x80018000,D[n]['addr'],D[n]['size']),autojunk=False).ratio()
  print(hex(a),sz[a],n,D[n]['size'],'%.2f'%s)
