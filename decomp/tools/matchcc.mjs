// Parameterized matcher: pick the cc1psx via CC1 env var.
//   CC1=D:/Tools/psyq4.3/CC1PSX.EXE node tools/matchcc.mjs <src.c> <addrHex> <size> [-O2] [-G0]
import { readFileSync } from 'node:fs';
import { assemble } from 'psyq-asm';
import { cc1, dmpsx } from './psyq.mjs';

// THPS1's compiler is PsyQ 4.5 (GCC 2.8.1), -O2 -G0 — verified byte-exact on VECTOR.
const RETAIL = "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const TEXT_ADDR = 0x80010000, HDR = 0x800;

const [src, addrHex, sizeStr, ...flags] = process.argv.slice(2);
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let g = 0, opt = '-O2';
for (const f of flags) { if (f === '-G8') g = 8; else if (f === '-G0') g = 0; else if (f.startsWith('-O')) opt = f; }

const sfile = `build/cc_${process.pid}.s`;
try {
  cc1(src, sfile, opt, g);
} catch (e) { console.log('COMPILE FAILED'); process.exit(1); }
const a = assemble(readFileSync(sfile, 'utf8'), { gpSize: g });
if (!a.success) { console.log('ASM FAILED'); process.exit(1); }
const got = dmpsx(Array.from(a.object.sections.find(s => s.name === '.text').words));

const off = addr - TEXT_ADDR + HDR;
const buf = readFileSync(RETAIL).subarray(off, off + size);
const want = []; for (let i = 0; i < size; i += 4) want.push(buf.readUInt32LE(i));
let same = 0; for (let i = 0; i < want.length; i++) if (got[i] === want[i]) same++;
const exact = same === want.length && got.length === want.length;
console.log(`${same}/${want.length}${exact ? '  >>> EXACT <<<' : ''}`);
