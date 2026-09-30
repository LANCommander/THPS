// Matcher with relocation resolution ("linker-lite") for global-referencing functions.
// THPS1 is -G8: small globals are addressed gp-relative (gp = 0x800d1080). Reference a global
// by name in the C (define it, e.g. `unsigned char g;`), provide its address in a symbol map,
// and this resolves psyq-asm's GPREL16/HI16/LO16 relocations before byte-diffing vs SLUS_008.60.
//
// Usage: node tools/match_sym.mjs <src.c> <retailAddrHex> <size> <syms.json> [-O2]
//   syms.json: { "gp": "0x800d1080", "<name>": "0x........", ... }
import { readFileSync } from 'node:fs';
import { assemble, decodeWords } from 'psyq-asm';
import { cc1, dmpsx } from './psyq.mjs';

const RETAIL = "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const TEXT_ADDR = 0x80010000, HDR = 0x800, G = 8;

const [src, addrHex, sizeStr, symPath, ...flags] = process.argv.slice(2);
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let opt = '-O2';
for (const f of flags) if (f.startsWith('-O')) opt = f;
const syms = JSON.parse(readFileSync(symPath, 'utf8'));
const gp = parseInt(syms.gp, 16);
const symAddr = n => { const v = syms[n]; if (v === undefined) throw new Error('unknown symbol ' + n); return parseInt(v, 16); };

const sfile = `build/sym_${process.pid}.s`;
cc1(src, sfile, opt, G);
const a = assemble(readFileSync(sfile, 'utf8'), { gpSize: G });
const sec = a.object.sections.find(s => s.name === '.text');
const words = dmpsx(Array.from(sec.words));

// apply relocations
for (const r of sec.relocations) {
  const i = r.offset >> 2;
  // local label (control flow) → function base + section offset; else symbol map
  const s = r.target.kind === 'section'
    ? addr + (r.target.offset | 0)
    : symAddr(r.target.name) + (r.target.addend | 0);
  let field;
  if (r.kind === 'GPREL16') field = (s - gp) & 0xFFFF;
  else if (r.kind === 'LO16') field = s & 0xFFFF;
  else if (r.kind === 'HI16') field = ((s + 0x8000) >>> 16) & 0xFFFF;   // paired-carry
  else if (r.kind === 'MIPS26') field = (s >>> 2) & 0x03FFFFFF;         // jal/j target
  else throw new Error('unhandled reloc ' + r.kind);
  words[i] = ((words[i] & ~(r.fieldMask >>> 0)) | (field & r.fieldMask)) >>> 0;
}

const off = addr - TEXT_ADDR + HDR;
const buf = readFileSync(RETAIL).subarray(off, off + size);
const want = []; for (let k = 0; k < size; k += 4) want.push(buf.readUInt32LE(k));
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const f = o => o.kind === 'gpr' ? R[o.number] : o.kind === 'mem' ? `${o.offset}(${R[o.base]})` : o.kind === 'imm' ? o.value : (o.target ?? '');
const fm = w => decodeWords(Uint32Array.from(w)).instructions.map(i => `${i.mnemonic} ${(i.operands||[]).map(f).join(',')}`);
const gA = fm(words), wA = fm(want);
let same = 0;
for (let i = 0; i < Math.max(words.length, want.length); i++) {
  const ok = words[i] === want[i]; if (ok) same++;
  if (!ok || process.env.V) console.log(`${String(i).padStart(2)} ${(gA[i]||'').padEnd(20)} | ${(wA[i]||'').padEnd(20)} ${ok?'':'X'}`);
}
console.log(`${same}/${want.length}${same===want.length&&words.length===want.length?'  >>> EXACT <<<':''}`);
