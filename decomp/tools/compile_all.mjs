// Compile every src/**/*.c and *.cpp to build/<tag>/ with the matchers' pipeline (parallel), for before/after checks of
// source-wide edits: run with one tag before, another after, and diff the two directories.
//   node tools/compile_all.mjs pre   ...edit...   node tools/compile_all.mjs post
import { execFile } from 'node:child_process';
import { promisify } from 'node:util';
import { readdirSync, statSync, mkdirSync, writeFileSync } from 'node:fs';
import { cpus } from 'node:os';
const run = promisify(execFile), tag = process.argv[2];
const files = []; (function walk(d) { for (const e of readdirSync(d)) { const p = `${d}/${e}`; if (statSync(p).isDirectory()) walk(p); else if (/\.(c|cpp)$/.test(p)) files.push(p); } })('src');
let i = 0;
async function worker() {
  while (i < files.length) {
    const f = files[i++], out = `build/${tag}/${f.replace(/\//g, '__')}.s`;
    try { await run('node', ['tools/compile.mjs', f, '-o', out]); } catch { writeFileSync(out + '.FAIL', ''); }
  }
}
mkdirSync(`build/${tag}`, { recursive: true });
await Promise.all(Array.from({ length: cpus().length }, worker));
console.log(files.length, 'compiled');
