// First-draft C for a retail function via m2c (mips_to_c, cloned into ../tools/vendor/m2c).
// Emits the function as GNU-as MIPS (labels, call names, %hi/%lo and %gp_rel symbol refs for
// globals, bare `div $zero,…`), then runs m2c on it. The draft is a starting point for matching,
// not matching C: expect to restructure it and apply the README patterns.
//
// Usage: node tools/m2c.mjs <addrHex> [size] [--asm] [--m2c-args "..."]
//   --asm   print the generated assembly instead of running m2c
import { readFileSync, writeFileSync, existsSync, mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { decodeWords } from 'psyq-asm';
import { retailWords } from './psyq.mjs';

const M2C = fileURLToPath(new URL('../../tools/vendor/m2c/m2c.py', import.meta.url));
const NAMES = "G:/Decompilation/Tony Hawk's Pro Skater/build/retail_names.tsv";
const GP = 0x800d1080;

const args = process.argv.slice(2);
const addr = parseInt(args[0], 16);
const names = new Map(), sizes = new Map();
if (existsSync(NAMES)) for (const l of readFileSync(NAMES, 'utf8').split('\n')) {
  const [a, s, k, n] = l.trim().split('\t');
  if (k === 'F' && !names.has(parseInt(a, 16))) { names.set(parseInt(a, 16), n); sizes.set(parseInt(a, 16), +s); }
}
for (const l of readFileSync(new URL('../functions.tsv', import.meta.url), 'utf8').split('\n')) {
  if (!l.trim() || l.startsWith('#')) continue;
  const [a, s, n] = l.trim().split('\t'), k = parseInt(a, 16);
  if (!sizes.has(k)) sizes.set(k, +s);
  if (!names.has(k)) names.set(k, n);
}
const size = args[1] && !args[1].startsWith('--') ? parseInt(args[1], 10) : sizes.get(addr);
if (!size) { console.error('size unknown: pass it explicitly'); process.exit(1); }
const fname = t => names.get(t) ?? `FUN_${t.toString(16)}`;
const sym = a => names.get(a) ?? `DAT_${(a >>> 0).toString(16)}`;

// GTE command word -> INLINE_C.H macro name(s), via the DMPSX table in reverse
const gteNames = new Map();
try {
  const table = JSON.parse(readFileSync(new URL('./dmpsx_table.json', import.meta.url), 'utf8'));
  const inc = readFileSync((process.env.PSYQ_INC || 'D:/Tools/psyq4.5/include') + '/INLINE_C.H', 'latin1');
  for (const m of inc.matchAll(/#define\s+(gte_\w+)\([^)]*\)[^#]*?\.word\s+(0x[0-9a-fA-F]+)/g)) {
    const real = table['0x' + parseInt(m[2], 16).toString(16).padStart(8, '0')];
    if (real) gteNames.set(parseInt(real, 16) >>> 0, [...(gteNames.get(parseInt(real, 16) >>> 0) || []), m[1]]);
  }
} catch { /* headers not installed: plain words */ }

const w = retailWords(addr, size >> 2);
const ins = decodeWords(Uint32Array.from(w)).instructions;
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const hex = v => (v < 0 ? '-0x' + (-v).toString(16) : '0x' + v.toString(16));
const lab = i => `.L${(addr + 4 * i).toString(16).toUpperCase()}`;

// pass 1: branch/jump labels, and lui -> first dependent low-half user (for %hi/%lo symbols)
const labels = new Set(), hiSym = new Map(), loRef = new Map();
ins.forEach((x, i) => {
  for (const o of x.operands || []) {
    if (o.kind === 'branch') labels.add(i + 1 + o.displacement);
    if (o.kind === 'target') { const t = (((addr + 4 * i) & 0xF0000000) | (o.index << 2)) >>> 0; if (t >= addr && t < addr + size) labels.add((t - addr) >> 2); }
  }
});
ins.forEach((x, i) => {
  if (x.mnemonic !== 'lui') return;
  const r = x.operands[0].number, hi = x.operands[1].value << 16;
  for (let j = i + 1; j < ins.length && j < i + 40; j++) {
    const y = ins[j], ops = y.operands || [];
    const mem = ops.find(o => o.kind === 'mem' && o.base === r);
    const isAddiu = (y.mnemonic === 'addiu' || y.mnemonic === 'ori') && ops[1]?.number === r;
    if (mem || isAddiu) {
      const target = (hi + (mem ? mem.offset : (y.mnemonic === 'ori' ? ops[2].value : ops[2].value))) >>> 0;
      if (!hiSym.has(i)) hiSym.set(i, target);
      loRef.set(j, { base: hiSym.get(i), target });
    }
    if (ops[0]?.kind === 'gpr' && ops[0].number === r && !(mem && y.mnemonic.startsWith('s'))) break;   // r redefined
  }
});
const symExpr = (base, target) => target === base ? sym(base) : `${sym(base)} + ${hex(target - base)}`;

// pass 2: emit
const out = [`glabel ${fname(addr)}`];
ins.forEach((x, i) => {
  if (labels.has(i)) out.push(`${lab(i)}:`);
  const ops = x.operands || [], lo = loRef.get(i);
  const f = (o, k) => {
    if (o.kind === 'gpr') return '$' + R[o.number];
    if (o.kind === 'cop') return '$' + o.number;
    if (o.kind === 'shamt') return String(o.value);
    if (o.kind === 'imm') {
      if (x.mnemonic === 'lui' && hiSym.has(i)) return `%hi(${sym(hiSym.get(i))})`;
      if (lo && k === 2) return `%lo(${symExpr(lo.base, lo.target)})`;
      return hex(o.value);
    }
    if (o.kind === 'mem') {
      if (o.base === 28) return `%gp_rel(${sym((GP + o.offset) >>> 0)})($gp)`;
      if (lo) return `%lo(${symExpr(lo.base, lo.target)})($${R[o.base]})`;
      return `${hex(o.offset)}($${R[o.base]})`;
    }
    if (o.kind === 'branch') return lab(i + 1 + o.displacement);
    if (o.kind === 'target') { const t = (((addr + 4 * i) & 0xF0000000) | (o.index << 2)) >>> 0; return t >= addr && t < addr + size ? lab((t - addr) >> 2) : fname(t); }
    return String(o.value ?? o.number ?? '');
  };
  let m = x.mnemonic, s;
  if (w[i] === 0) s = 'nop';
  else if (m === '.word' || m === undefined) s = `.word 0x${w[i].toString(16)}`;
  else if ((m === 'div' || m === 'divu' || m === 'mult' || m === 'multu') && ops.length === 2) s = `${m} $zero, ${ops.map(f).join(', ')}`;
  else if (m === 'cop2') s = `.word 0x${w[i].toString(16)} /* cop2: ${(gteNames.get(w[i]) || ['?']).join(' / ')} */`;
  else s = `${m} ${ops.map(f).join(', ')}`.trim();
  out.push(`/* ${(addr + 4 * i).toString(16).toUpperCase()} ${w[i].toString(16).padStart(8, '0').toUpperCase()} */  ${s}`);
});
const asm = out.join('\n') + '\n';
if (args.includes('--asm')) { process.stdout.write(asm); process.exit(0); }

mkdirSync('build', { recursive: true });
const f = `build/m2c_${process.pid}.s`;
writeFileSync(f, '.set noat\n.set noreorder\n' + asm);
const extra = args.includes('--m2c-args') ? args[args.indexOf('--m2c-args') + 1].split(' ') : [];
try {
  process.stdout.write(execFileSync('python', [M2C, '-t', 'mipsel-gcc-c', ...extra, f], { encoding: 'utf8' }));
} catch (e) { process.stdout.write((e.stdout || '') + (e.stderr || '')); process.exit(1); }
