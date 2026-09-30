// Re-verify every function listed in matched.tsv with its matcher; exits non-zero on any regression.
// Usage: node tools/check_all.mjs [filterSubstring]
import { readFileSync, existsSync } from 'node:fs';
import { execFile } from 'node:child_process';
import { promisify } from 'node:util';
import { cpus } from 'node:os';

const run = promisify(execFile);
const filter = process.argv[2] ?? '';
const rows = readFileSync('matched.tsv', 'utf8').split('\n')
  .filter(l => l.trim() && !l.startsWith('#')).map(l => l.split('\t'))
  .filter(r => r.join(' ').includes(filter));

async function check([src, addr, size, tool, name]) {
  const syms = src.replace(/\.c$/, '.syms.json');
  const cmd = {
    cc: ['node', ['tools/matchcc.mjs', src, addr, size, '-O2', '-G0']],
    sym: ['node', ['tools/match_sym.mjs', src, addr, size, syms, '-O2']],
    div: ['python', ['tools/match_div.py', src, addr, size, ...(existsSync(syms) ? [syms] : []), '-O2', '-G8']],
  }[tool];
  let out;
  try { out = (await run(...cmd)).stdout; } catch (e) { out = (e.stdout || '') + (e.stderr || e.message); }
  const last = out.trim().split('\n').pop();
  return { name, src, ok: last.includes('EXACT'), last };
}

const results = [];
const queue = [...rows];
await Promise.all(Array.from({ length: Math.max(1, cpus().length - 1) }, async () => {
  while (queue.length) results.push(await check(queue.shift()));
}));
results.sort((a, b) => a.src.localeCompare(b.src));
for (const r of results) console.log(`${r.ok ? 'ok  ' : 'FAIL'} ${r.src.padEnd(34)} ${r.last}`);
const bad = results.filter(r => !r.ok).length;
console.log(`\n${results.length - bad}/${results.length} exact`);
process.exit(bad ? 1 : 0);
