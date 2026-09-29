// Full matching pipeline: C -> cc1psx (psyq-wasm) -> ASPSX (psyq-asm) -> R3000 words,
// compared word-for-word against the real function bytes in the retail executable.
//
// Usage: node tools/match.mjs <src.c> <retailAddrHex> <sizeBytes> [-G0|-G8] [-O2 ...]
import { readFileSync } from 'node:fs';
import { createCompiler, DEFAULT_CPP_FLAGS } from 'psyq-wasm';
import { assemble, decodeWords } from 'psyq-asm';

const RETAIL = 'G:/Decompilation/Tony Hawk\'s Pro Skater/extern/thps1_retail/SLUS_008.60';
const TEXT_ADDR = 0x80010000, HDR = 0x800;

const [src, addrHex, sizeStr, ...flags] = process.argv.slice(2);
if (!src || !addrHex || !sizeStr) {
  console.error('usage: match.mjs <src.c> <retailAddrHex> <sizeBytes> [-G0|-G8] [flags]');
  process.exit(2);
}
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let gpSize = 8;
const rawFlags = ['-O2', '-g0'];
for (const f of flags) {
  if (f === '-G0') gpSize = 0; else if (f === '-G8') gpSize = 8;
  else if (f.startsWith('-O')) rawFlags[0] = f; else rawFlags.push(f);
}

// 1. compile
const compiler = await createCompiler();
const c = await compiler.compileSource(readFileSync(src, 'utf8'),
  { gpSize, filename: src.split(/[\\/]/).pop(), rawFlags, cppFlags: [...DEFAULT_CPP_FLAGS] });
compiler.dispose();
if (!c.success) { console.error('compile failed', c.diagnostics); process.exit(1); }

// 2. assemble
const a = assemble(c.text, { gpSize });
if (!a.success) { console.error('assemble failed', a.diagnostics); process.exit(1); }
const textSec = a.object.sections.find(s => s.name === '.text');
const got = Array.from(textSec.words);

// 3. target bytes from retail
const off = addr - TEXT_ADDR + HDR;
const buf = readFileSync(RETAIL).subarray(off, off + size);
const want = [];
for (let i = 0; i < size; i += 4) want.push(buf.readUInt32LE(i));

// 4. compare
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7',
  's0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const fmtOp = o => o.kind === 'gpr' ? R[o.number]
  : o.kind === 'mem' ? `${o.offset}(${R[o.base]})`
  : o.kind === 'imm' ? String(o.value) : (o.target ?? JSON.stringify(o));
const fmt = arr => (arr?.instructions ?? []).map(i => `${i.mnemonic} ${(i.operands||[]).map(fmtOp).join(',')}`.trim());
const gotAsm = fmt(decodeWords(Uint32Array.from(got)));
const wantAsm = fmt(decodeWords(Uint32Array.from(want)));
const n = Math.max(got.length, want.length);
let same = 0;
console.log(`idx  GOT(word)  WANT(word)  ok   ${'GOT asm'.padEnd(22)} WANT asm`);
for (let i = 0; i < n; i++) {
  const g = got[i], w = want[i];
  const ok = g === w; if (ok) same++;
  const gh = g === undefined ? '        ' : g.toString(16).padStart(8, '0');
  const wh = w === undefined ? '        ' : w.toString(16).padStart(8, '0');
  console.log(`${String(i).padStart(2)}  ${gh}  ${wh}  ${ok ? ' ' : 'X'}   ${(gotAsm[i]||'').padEnd(22)} ${wantAsm[i]||''}`);
}
console.log(`\n${same}/${want.length} words identical (${(same/want.length*100).toFixed(0)}%)` +
  (same === want.length && got.length === want.length ? '  >>> BYTE-EXACT MATCH <<<' : ''));
