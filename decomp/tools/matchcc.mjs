// Parameterized matcher: pick the cc1psx via CC1 env var.
//   CC1=D:/Tools/psyq4.3/CC1PSX.EXE node tools/matchcc.mjs <src.c> <addrHex> <size> [-O2] [-G0]
import { readFileSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { assemble } from 'psyq-asm';

// THPS1's compiler is PsyQ 4.5 (GCC 2.8.1), -O2 -G0 — verified byte-exact on VECTOR.
const CC1 = process.env.CC1 || 'D:/Tools/psyq4.5/CC1PSX.EXE';
const RETAIL = "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const TEXT_ADDR = 0x80010000, HDR = 0x800;

const [src, addrHex, sizeStr, ...flags] = process.argv.slice(2);
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let g = 0, opt = '-O2';
for (const f of flags) { if (f === '-G8') g = 8; else if (f === '-G0') g = 0; else if (f.startsWith('-O')) opt = f; }

const cfile = `build_cc_${process.pid}.i`, sfile = `build_cc_${process.pid}.s`;
writeFileSync(cfile, readFileSync(src, 'utf8'));
try {
  execFileSync(CC1, [cfile, '-quiet', ...opt.split(' '), `-G${g}`, '-o', sfile], { stdio: ['ignore', 'ignore', 'ignore'] });
} catch (e) { console.log('COMPILE FAILED'); process.exit(1); }
const a = assemble(readFileSync(sfile, 'utf8'), { gpSize: g });
if (!a.success) { console.log('ASM FAILED'); process.exit(1); }
const got = Array.from(a.object.sections.find(s => s.name === '.text').words);

const off = addr - TEXT_ADDR + HDR;
const buf = readFileSync(RETAIL).subarray(off, off + size);
const want = []; for (let i = 0; i < size; i += 4) want.push(buf.readUInt32LE(i));
let same = 0; for (let i = 0; i < want.length; i++) if (got[i] === want[i]) same++;
const exact = same === want.length && got.length === want.length;
console.log(`${same}/${want.length}${exact ? '  >>> EXACT <<<' : ''}`);
