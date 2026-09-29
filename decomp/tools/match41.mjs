// Matching pipeline using the NATIVE PsyQ 4.0 cc1psx (GCC 2.7.2) on Windows.
//   C -> CC1PSX.EXE (2.7.2) -> PsyQ asm -> psyq-asm (ASPSX) -> R3000 words -> diff vs SLUS_008.60
//
// Usage: node tools/match272.mjs <src.c> <retailAddrHex> <sizeBytes> [-G0|-G8] [-O2]
import { readFileSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { assemble, decodeWords } from 'psyq-asm';

const CC1 = 'D:/Tools/psyq4.1/CC1PSX.EXE';
const RETAIL = "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const TEXT_ADDR = 0x80010000, HDR = 0x800;

const [src, addrHex, sizeStr, ...flags] = process.argv.slice(2);
if (!src || !addrHex || !sizeStr) { console.error('usage: match272.mjs <src.c> <addrHex> <size> [-G0|-G8] [-O2]'); process.exit(2); }
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let g = 0, opt = '-O2';                       // THPS1: gp=0 -> -G0
for (const f of flags) { if (f === '-G8') g = 8; else if (f === '-G0') g = 0; else if (f.startsWith('-O')) opt = f; }

// 1. compile with cc1psx 2.7.2 (plain C w/o includes == preprocessed .i)
const cfile = 'build_272.i', sfile = 'build_272.s';
writeFileSync(cfile, readFileSync(src, 'utf8'));
execFileSync(CC1, [cfile, '-quiet', opt, `-G${g}`, '-o', sfile], { stdio: ['ignore', 'inherit', 'inherit'] });
const asmText = readFileSync(sfile, 'utf8');

// 2. assemble with psyq-asm
const a = assemble(asmText, { gpSize: g });
if (!a.success) { console.error('assemble failed', a.diagnostics); process.exit(1); }
const got = Array.from(a.object.sections.find(s => s.name === '.text').words);

// 3. target bytes
const off = addr - TEXT_ADDR + HDR;
const buf = readFileSync(RETAIL).subarray(off, off + size);
const want = []; for (let i = 0; i < size; i += 4) want.push(buf.readUInt32LE(i));

// 4. compare
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const fmtOp = o => o.kind==='gpr'?R[o.number]:o.kind==='mem'?`${o.offset}(${R[o.base]})`:o.kind==='imm'?String(o.value):(o.target??'');
const fmt = arr => (arr?.instructions ?? []).map(i => `${i.mnemonic} ${(i.operands||[]).map(fmtOp).join(',')}`.trim());
const gA = fmt(decodeWords(Uint32Array.from(got))), wA = fmt(decodeWords(Uint32Array.from(want)));
let same = 0; const n = Math.max(got.length, want.length);
console.log(`idx  GOT       WANT        ${'GOT asm'.padEnd(20)} WANT asm`);
for (let i = 0; i < n; i++) {
  const ok = got[i] === want[i]; if (ok) same++;
  const gh = got[i]===undefined?'        ':got[i].toString(16).padStart(8,'0');
  const wh = want[i]===undefined?'        ':want[i].toString(16).padStart(8,'0');
  console.log(`${String(i).padStart(2)}  ${gh}  ${wh} ${ok?' ':'X'}  ${(gA[i]||'').padEnd(20)} ${wA[i]||''}`);
}
console.log(`\n${same}/${want.length} words identical (${(same/want.length*100).toFixed(0)}%)` + (same===want.length&&got.length===want.length?'  >>> BYTE-EXACT <<<':''));
