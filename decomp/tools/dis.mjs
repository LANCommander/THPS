// Disassemble a retail SLUS_008.60 function, annotated for writing matching C:
// call/jump targets get their ported demo names, branches get local labels, gp-relative and
// lui/addiu|lw|sw pairs are resolved to absolute DAT_ addresses (the names to use in syms.json).
//
// Usage: node tools/dis.mjs <addrHex> [sizeBytes]     (size defaults to the functions.tsv entry)
//        DEMO=1 node tools/dis.mjs <demoAddrHex|demoName>  disassembles the THPS2 demo (PROSKATE.EXE) instead
import { readFileSync, existsSync } from 'node:fs';
import { decodeWords } from 'psyq-asm';

const DEMO = !!process.env.DEMO;
const RETAIL = DEMO ? "G:/Decompilation/Tony Hawk's Pro Skater/extern/demo/PROSKATE.EXE"
  : "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const NAMES = "G:/Decompilation/Tony Hawk's Pro Skater/build/retail_names.tsv";
const TEXT_ADDR = DEMO ? 0x80018000 : 0x80010000, HDR = 0x800, GP = DEMO ? 0 : 0x800d1080;

const names = new Map(), sizes = new Map();
if (DEMO) {
  for (const f of JSON.parse(readFileSync("G:/Decompilation/Tony Hawk's Pro Skater/build/MAIN_sym.json", 'utf8')).funcs) {
    names.set(f.addr >>> 0, f.name); sizes.set(f.addr >>> 0, f.size);
  }
} else if (existsSync(NAMES)) for (const l of readFileSync(NAMES, 'utf8').split('\n')) {
  const [a, s, k, n] = l.trim().split('\t');
  if (k === 'F' && !names.has(parseInt(a, 16))) { names.set(parseInt(a, 16), n); sizes.set(parseInt(a, 16), +s); }
}
// every game function, named or FUN_ (functions.tsv): sizes for the unnamed ones. Its names are the
// curated ones, so they win over the raw demo port; column 5 is the demangled form.
const written = new Map();
if (!DEMO) for (const l of readFileSync(new URL('../functions.tsv', import.meta.url), 'utf8').split('\n')) {
  if (!l.trim() || l.startsWith('#')) continue;
  const [a, s, n, , wr] = l.trim().split('\t'), k = parseInt(a, 16);
  if (!sizes.has(k)) sizes.set(k, +s);
  if (!names.has(k) || !n.startsWith('FUN_')) names.set(k, n);
  if (wr && wr !== n) written.set(k, wr);
}
let addr = parseInt(process.argv[2], 16);
if (DEMO && !/^(0x)?[0-9a-f]+$/i.test(process.argv[2])) addr = [...names].find(([, n]) => n === process.argv[2])?.[0];
const size = process.argv[3] ? parseInt(process.argv[3], 10) : sizes.get(addr);
if (!size) { console.error('size unknown: pass it explicitly'); process.exit(1); }

const b = readFileSync(RETAIL).subarray(addr - TEXT_ADDR + HDR, addr - TEXT_ADDR + HDR + size);
const w = []; for (let i = 0; i < size; i += 4) w.push(b.readUInt32LE(i));
const R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra'];
const hex = v => '0x' + (v >>> 0).toString(16);
const fname = t => names.get(t) ?? `FUN_${t.toString(16)}`;

const ins = decodeWords(Uint32Array.from(w)).instructions;
const labels = new Set();
ins.forEach((x, i) => { for (const o of x.operands || []) if (o.kind === 'branch') labels.add(i + 1 + o.displacement); });
const lui = {};   // reg -> hi value (tracked linearly; good enough for annotation)
console.log(`# ${names.get(addr) ?? fname(addr)}  @${hex(addr)}  ${size} bytes`);
if (written.has(addr)) console.log(`# as written: ${written.get(addr)}`);
ins.forEach((x, i) => {
  const pc = addr + 4 * i, ops = x.operands || [];
  let note = '';
  const f = o => {
    if (o.kind === 'gpr') return R[o.number];
    if (o.kind === 'imm') return o.value;
    if (o.kind === 'shamt') return o.value;
    if (o.kind === 'mem') {
      if (o.base === 28) note = `DAT_${((GP + o.offset) >>> 0).toString(16)} (gp)`;
      else if (lui[o.base] !== undefined) note = `DAT_${((lui[o.base] + o.offset) >>> 0).toString(16)}`;
      return `${o.offset}(${R[o.base]})`;
    }
    if (o.kind === 'branch') return `L${i + 1 + o.displacement}`;
    if (o.kind === 'target') { const t = ((pc & 0xF0000000) | (o.index << 2)) >>> 0; return t >= addr && t < addr + size ? `L${(t - addr) >> 2}` : fname(t); }
    return o.number ?? o.value ?? JSON.stringify(o);
  };
  const txt = `${x.mnemonic} ${ops.map(f).join(',')}`;
  if (x.mnemonic === 'lui') lui[ops[0].number] = (ops[1].value << 16) | 0;
  else if (x.mnemonic === 'addiu' && lui[ops[1]?.number] !== undefined) { note = `&DAT_${((lui[ops[1].number] + ops[2].value) >>> 0).toString(16)}`; }
  console.log(`${labels.has(i) ? `L${i}:`.padEnd(5) : '     '}${String(i).padStart(3)} ${w[i].toString(16).padStart(8, '0')}  ${txt.padEnd(34)}${note ? '; ' + note : ''}`);
});
