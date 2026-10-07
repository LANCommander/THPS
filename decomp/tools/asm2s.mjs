// Emit a hand-assembly source (.s) for a retail range that was written in assembly, not C.
// Every functions.tsv entry in the range becomes a global label, branches get local labels, and
// calls outside the range use their ported names (listed in the syms.json beside the .s).
// The result reassembles through psyq-asm under `.set noreorder`, the way the original was written.
//
// Usage: node tools/asm2s.mjs <addrHex> <sizeBytes> <out.s> [name]
// The first line is the salvage header (`# <name> (0x<addr>) size=<n>`), so the module merges like a C source.
import { readFileSync, writeFileSync } from 'node:fs';
import { decodeWords } from 'psyq-asm';
import { retailWords } from './psyq.mjs';

const [addrHex, sizeStr, out, title] = process.argv.slice(2);
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10), n = size >> 2;

const names = new Map();
for (const l of readFileSync("G:/Decompilation/Tony Hawk's Pro Skater/build/retail_names.tsv", 'utf8').split('\n')) {
  const [a, , k, nm] = l.trim().split('\t');
  if (k === 'F' && !names.has(parseInt(a, 16))) names.set(parseInt(a, 16), nm);
}
const entries = new Map();
for (const l of readFileSync(new URL('../functions.tsv', import.meta.url), 'utf8').split('\n')) {
  if (!l.startsWith('0x')) continue;
  const [a, , nm] = l.split('\t'), k = parseInt(a, 16);
  if (!names.has(k)) names.set(k, nm);
  if (k >= addr && k < addr + size) entries.set(k, nm);
}
const fname = t => names.get(t) ?? `FUN_${t.toString(16)}`;

const w = retailWords(addr, n);
const ins = decodeWords(Uint32Array.from(w)).instructions;
const labels = new Set();
ins.forEach((x, i) => { for (const o of x.operands || []) if (o.kind === 'branch') labels.add(i + 1 + o.displacement); });

const externs = new Set();
const lines = [`# ${title ?? `FUN_${addr.toString(16)}`} (0x${addr.toString(16)}) size=${size} -- hand-written assembly`,
  '\t.set\tnoreorder', '\t.set\tnoat', '\t.text', ''];
ins.forEach((x, i) => {
  const pc = addr + 4 * i;
  if (entries.has(pc)) lines.push(`\t.globl\t${entries.get(pc)}`, `${entries.get(pc)}:`);
  if (labels.has(i)) lines.push(`$L${i}:`);
  const ops = (x.operands || []).map(o => {
    if (o.kind === 'gpr') return `$${o.number}`;
    if (o.kind === 'imm' || o.kind === 'shamt') return String(o.value);
    if (o.kind === 'mem') return `${o.offset}($${o.base})`;
    if (o.kind === 'cop') return `$${o.number}`;
    if (o.kind === 'branch') return `$L${i + 1 + o.displacement}`;
    if (o.kind === 'target') {
      const t = ((pc & 0xF0000000) | (o.index << 2)) >>> 0;
      if (t >= addr && t < addr + size) return entries.get(t) ?? `$L${(t - addr) >> 2}`;
      externs.add(fname(t)); return fname(t);
    }
    return String(o.number ?? o.value);
  });
  lines.push(`\t${x.mnemonic}\t${ops.join(',')}`);
});
writeFileSync(out, lines.join('\n') + '\n');
console.log(`${out}: ${n} words, ${entries.size} entry labels, externs: ${[...externs].join(' ') || '-'}`);
