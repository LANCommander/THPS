// Compile a C file with PsyQ 4.4 cc1psx (via psyq-wasm) to MIPS assembly.
// Usage: node tools/compile.mjs <src.c> [-O2] [-G0|-G8] [-o out.s]
import { readFileSync, writeFileSync } from 'node:fs';
import { createCompiler, DEFAULT_CPP_FLAGS } from 'psyq-wasm';

const args = process.argv.slice(2);
const src = args[0];
if (!src) { console.error('usage: compile.mjs <src.c> [flags] [-o out.s]'); process.exit(1); }
let outPath = null;
let gpSize = 8;
const rawFlags = ['-O2', '-g0'];
for (let i = 1; i < args.length; i++) {
  const a = args[i];
  if (a === '-o') outPath = args[++i];
  else if (a === '-G0') gpSize = 0;
  else if (a === '-G8') gpSize = 8;
  else if (a.startsWith('-O') || a.startsWith('-g') || a.startsWith('-f') || a.startsWith('-W')) {
    // replace the -O level if given, else append
    const idx = rawFlags.findIndex(f => a.startsWith('-O') && f.startsWith('-O'));
    if (idx >= 0 && a.startsWith('-O')) rawFlags[idx] = a; else rawFlags.push(a);
  }
}

const compiler = await createCompiler();
const result = await compiler.compileSource(readFileSync(src, 'utf8'), {
  gpSize,
  filename: src.split(/[\\/]/).pop(),
  rawFlags,
  cppFlags: [...DEFAULT_CPP_FLAGS],
});
compiler.dispose();

if (!result.success) {
  console.error('COMPILE FAILED exit', result.exitCode);
  for (const d of result.diagnostics ?? []) console.error(`  ${d.severity} ${d.file}:${d.line}: ${d.message}`);
  process.exit(1);
}
if (outPath) { writeFileSync(outPath, result.text); console.error(`wrote ${outPath}`); }
else process.stdout.write(result.text);
