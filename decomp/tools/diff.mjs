// Compile a C file and diff its instructions against an expected target listing.
// Normalizes register aliases ($N <-> name) and immediate hex/dec so we compare
// instruction shape. Usage: node tools/diff.mjs <src.c> <expected.txt> [flags...]
import { execFileSync } from 'node:child_process';
import { readFileSync } from 'node:fs';

const [src, expected, ...flags] = process.argv.slice(2);
if (!src || !expected) { console.error('usage: diff.mjs <src.c> <expected.txt> [flags]'); process.exit(2); }

const REG = { $0:'zero',$1:'at',$2:'v0',$3:'v1',$4:'a0',$5:'a1',$6:'a2',$7:'a3',
  $8:'t0',$9:'t1',$10:'t2',$11:'t3',$12:'t4',$13:'t5',$14:'t6',$15:'t7',
  $16:'s0',$17:'s1',$18:'s2',$19:'s3',$20:'s4',$21:'s5',$22:'s6',$23:'s7',
  $24:'t8',$25:'t9',$26:'k0',$27:'k1',$28:'gp',$29:'sp',$30:'fp',$31:'ra' };

function norm(line) {
  let s = line.replace(/#.*$/, '').trim();
  if (!s) return null;
  if (/^[.]/.test(s) || /:$/.test(s) || /gcc2_compiled|__gnu/.test(s)) return null;
  s = s.replace(/\$\d+/g, m => REG[m] || m);           // $4 -> a0
  s = s.replace(/\b0x0+([0-9a-fA-F])/g, '0x$1');        // 0x00 -> 0x0-ish
  s = s.replace(/,\s*/g, ',').replace(/\s+/g, ' ');     // whitespace
  s = s.replace(/^_/, '');                               // ghidra's _sw etc.
  // canonicalize immediates: hex->dec
  s = s.replace(/0x([0-9a-fA-F]+)/g, (_, h) => String(parseInt(h, 16)));
  return s.trim();
}

const asm = execFileSync(process.execPath, ['tools/compile.mjs', src, ...(flags.length?flags:['-O2','-G8'])],
  { encoding: 'utf8', maxBuffer: 1 << 24 });
const got = asm.split(/\r?\n/).map(norm).filter(Boolean);
const want = readFileSync(expected, 'utf8').split(/\r?\n/).map(norm).filter(Boolean);

const n = Math.max(got.length, want.length);
let match = 0;
console.log(`idx ${'GOT'.padEnd(22)} ${'WANT'.padEnd(22)} ok`);
for (let i = 0; i < n; i++) {
  const g = got[i] ?? '', w = want[i] ?? '';
  const ok = g === w; if (ok) match++;
  console.log(`${String(i).padStart(2)} ${g.padEnd(22)} ${w.padEnd(22)} ${ok ? '' : 'X'}`);
}
const pct = (match / want.length * 100).toFixed(0);
console.log(`\n${match}/${want.length} instructions match (${pct}%)  ${match===want.length&&got.length===want.length?'>>> EXACT MATCH <<<':''}`);
