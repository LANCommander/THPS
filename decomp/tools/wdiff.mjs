// Alignment-aware diff of two R3000 word streams, for matchers that don't link through psyq-asm
// (match_div.py with D=1). Reads {"mine":[...],"retail":[...]} JSON and prints only the differing
// hunks, disassembled, like match_sym.mjs D=1.
//
// Usage: node tools/wdiff.mjs <words.json>
import { readFileSync } from 'node:fs';
import { decodeWords } from 'psyq-asm';

const { mine: words, retail: want } = JSON.parse(readFileSync(process.argv[2], 'utf8'));
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const f = o => o.kind === 'gpr' ? R[o.number] : o.kind === 'mem' ? `${o.offset}(${R[o.base]})` : o.kind === 'imm' ? o.value : (o.target ?? '');
const fm = w => decodeWords(Uint32Array.from(w)).instructions.map(i => `${i.mnemonic} ${(i.operands||[]).map(f).join(',')}`);
const gA = fm(words), wA = fm(want);
const n = words.length, m = want.length, L = Array.from({ length: n + 1 }, () => new Uint16Array(m + 1));
for (let i = n - 1; i >= 0; i--) for (let j = m - 1; j >= 0; j--)
  L[i][j] = words[i] === want[j] ? L[i + 1][j + 1] + 1 : Math.max(L[i + 1][j], L[i][j + 1]);
let i = 0, j = 0, mine = [], ret = [];
const flush = () => {
  if (!mine.length && !ret.length) return;
  console.log(`@@ mine ${mine[0] ?? i} | retail ${ret[0] ?? j}`);
  for (let k = 0; k < Math.max(mine.length, ret.length); k++)
    console.log(`  ${(mine[k] !== undefined ? `${mine[k]} ${gA[mine[k]]}` : '').padEnd(30)} | ${ret[k] !== undefined ? `${ret[k]} ${wA[ret[k]]}` : ''}`);
  mine = []; ret = [];
};
while (i < n || j < m) {
  if (i < n && j < m && words[i] === want[j]) { flush(); i++; j++; }
  else if (j >= m || (i < n && L[i + 1][j] >= L[i][j + 1])) mine.push(i++);
  else ret.push(j++);
}
flush();
