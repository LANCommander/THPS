// Compile a C file to MIPS assembly with exactly the matchers' pipeline (CPPPSX + native PsyQ 4.5
// CC1PSX.EXE), so the .s you inspect is what gets matched.
// Usage: node tools/compile.mjs <src.c> [-O2] [-G0|-G8] [-o out.s]     (defaults: -O2 -G8)
import { readFileSync, writeFileSync } from 'node:fs';
import { cc1 } from './psyq.mjs';

const args = process.argv.slice(2);
const src = args[0];
if (!src) { console.error('usage: compile.mjs <src.c> [-O2] [-G0|-G8] [-o out.s]'); process.exit(1); }
let outPath = null, g = 8, opt = '-O2';
for (let i = 1; i < args.length; i++) {
  const a = args[i];
  if (a === '-o') outPath = args[++i];
  else if (a === '-G0') g = 0;
  else if (a === '-G8') g = 8;
  else if (a.startsWith('-O')) opt = a;
}

const sfile = `build/compile_${process.pid}.s`;
try { cc1(src, sfile, opt, g); }
catch { console.error('COMPILE FAILED (cc1 is C89: declarations before statements)'); process.exit(1); }
const text = readFileSync(sfile, 'utf8');
if (outPath) { writeFileSync(outPath, text); console.error(`wrote ${outPath}`); }
else process.stdout.write(text);
