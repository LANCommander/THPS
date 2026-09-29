// Lightweight permuter integrated with the psyq4.5 + psyq-asm + reloc-resolve pipeline.
// Generates C variants (commutative operand swaps, temp introduction, statement/decl reorder)
// and scores each against the retail target, searching for a byte-exact match.
//
// Usage: node tools/permute.mjs <src.c> <addrHex> <size> <syms.json> [-O2] [--iters N]
import { readFileSync, writeFileSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { assemble } from 'psyq-asm';

const CC1 = process.env.CC1 || 'D:/Tools/psyq4.5/CC1PSX.EXE';
const RETAIL = "G:/Decompilation/Tony Hawk's Pro Skater/extern/thps1_retail/SLUS_008.60";
const TEXT_ADDR = 0x80010000, HDR = 0x800, G = 8;

const args = process.argv.slice(2);
const [src, addrHex, sizeStr, symPath] = args;
const addr = parseInt(addrHex, 16), size = parseInt(sizeStr, 10);
let opt = '-O2';
const iters = args.includes('--iters') ? parseInt(args[args.indexOf('--iters') + 1]) : 3000;
for (const f of args) if (f.startsWith('-O')) opt = f;
const syms = JSON.parse(readFileSync(symPath, 'utf8'));
const gp = parseInt(syms.gp, 16);
const symAddr = n => parseInt(syms[n], 16);

const off = addr - TEXT_ADDR + HDR;
const wbuf = readFileSync(RETAIL).subarray(off, off + size);
const want = []; for (let k = 0; k < size; k += 4) want.push(wbuf.readUInt32LE(k));

let tmp = 0;
function score(csrc) {
  const cf = `perm_${process.pid}_${tmp}.c`, sf = `perm_${process.pid}_${tmp}.s`; tmp = (tmp + 1) & 7;
  writeFileSync(cf, csrc);
  try { execFileSync(CC1, [cf, '-quiet', ...opt.split(' '), `-G${G}`, '-o', sf], { stdio: 'ignore' }); }
  catch { return -1; }
  let a; try { a = assemble(readFileSync(sf, 'utf8'), { gpSize: G }); } catch { return -1; }
  if (!a.success) return -1;
  const sec = a.object.sections.find(s => s.name === '.text');
  const words = Array.from(sec.words);
  for (const r of sec.relocations) {
    const i = r.offset >> 2;
    const s = r.target.kind === 'section' ? addr + (r.target.offset | 0) : symAddr(r.target.name) + (r.target.addend | 0);
    let field;
    if (r.kind === 'GPREL16') field = (s - gp) & 0xFFFF;
    else if (r.kind === 'LO16') field = s & 0xFFFF;
    else if (r.kind === 'HI16') field = ((s + 0x8000) >>> 16) & 0xFFFF;
    else if (r.kind === 'MIPS26') field = (s >>> 2) & 0x03FFFFFF;
    else return -1;
    words[i] = ((words[i] & ~(r.fieldMask >>> 0)) | (field & r.fieldMask)) >>> 0;
  }
  if (words.length !== want.length) return Math.min(words.length, want.length) - 100; // penalise size mismatch
  let same = 0; for (let i = 0; i < want.length; i++) if (words[i] === want[i]) same++;
  return same;
}

// --- mutation generators (return a mutated copy of the source, or null) ---
// Canonicalise: collapse alias temps (`T _a = _b;` -> use _b), drop unused temps.
function cleanup(csrc) {
  let lines = csrc.split('\n');
  const count = (arr, n) => arr.join('\n').split(new RegExp(`\\b${n}\\b`)).length - 1;
  let changed = true;
  while (changed) {
    changed = false;
    for (let i = 0; i < lines.length; i++) {
      const a = lines[i].match(/^\s*(?:unsigned|int|char|short|long)\s+(_t\d+)\s*=\s*([A-Za-z_]\w*)\s*;\s*$/);
      if (a && a[1] !== a[2]) {                       // alias temp
        lines.splice(i, 1);
        lines = lines.map(l => l.replace(new RegExp(`\\b${a[1]}\\b`, 'g'), a[2]));
        changed = true; break;
      }
      const d = lines[i].match(/^\s*(?:unsigned|int|char|short|long)\s+(_t\d+)\s*=/);
      if (d && count(lines, d[1]) <= 1) { lines.splice(i, 1); changed = true; break; }   // unused
    }
  }
  return lines.join('\n');
}

function mutate(csrc, rng) {
  const kind = Math.floor(rng() * 4);
  if (kind === 3) { const c = cleanup(csrc); return c === csrc ? null : c; }
  const lines = csrc.split('\n');
  const isDecl = l => /^\s*(int|unsigned|char|short|long|void)\b/.test(l);
  if (kind === 0) {
    // swap operands of `A OP B` (OP commutative) inside one line, where A/B are simple terms
    const li = Math.floor(rng() * lines.length);
    const line = lines[li];
    // match  term OP term  with terms being ident / ident[...] / (paren) / number, no nested change
    const re = /([A-Za-z_]\w*(?:\[[^\]]*\])?|\([^()]+\)|0x[0-9a-fA-F]+|\d+)\s*([+^|&*])\s*([A-Za-z_]\w*(?:\[[^\]]*\])?|\([^()]+\)|0x[0-9a-fA-F]+|\d+)/g;
    const hits = [...line.matchAll(re)];
    if (!hits.length) return null;
    const h = hits[Math.floor(rng() * hits.length)];
    const swapped = `${h[3]} ${h[2]} ${h[1]}`;
    const nl = lines.slice(); nl[li] = line.slice(0, h.index) + swapped + line.slice(h.index + h[0].length);
    return nl.join('\n');
  } else if (kind === 1) {
    // introduce a temp for a `X & MASK`, `X >> N`, or paren subexpr — works on decl or stmt lines
    const li = Math.floor(rng() * lines.length);
    if (/^\s*(extern|void f|.*\bf\s*\()/.test(lines[li]) && !/=/.test(lines[li])) return null;
    const m = lines[li].match(/([A-Za-z_]\w*\s*(?:&|>>|<<|\+|\^|\|)\s*(?:0x[0-9a-fA-F]+|\d+|[A-Za-z_]\w*))/) ||
              lines[li].match(/\(([^()]{4,})\)/);
    if (!m) return null;
    const expr = m[1];
    const name = `_t${Math.floor(rng() * 10000)}`;
    const indent = lines[li].match(/^\s*/)[0];
    const rep = lines[li].replace(expr, name);
    const nl = lines.slice(); nl.splice(li, 0, `${indent}unsigned ${name} = ${expr};`); nl[li + 1] = rep;
    return nl.join('\n');
  } else {
    // swap two adjacent independent statements or temp declarations
    const reorderable = l => /;\s*$/.test(l) && !/(return|if|else|do|while|for)\b/.test(l) &&
      (!isDecl(l) || /^\s*(?:unsigned|int|char|short|long)\s+_t\d+\s*=/.test(l));
    const idx = lines.map((l, i) => reorderable(l) ? i : -1).filter(i => i >= 0);
    for (let t = 0; t < 8; t++) {
      const j = idx[Math.floor(rng() * idx.length)]; const k = j + 1;
      if (!idx.includes(k)) continue;
      const idsA = lines[j].match(/[A-Za-z_]\w*/g) || [], idsB = lines[k].match(/[A-Za-z_]\w*/g) || [];
      const lhsA = (lines[j].split('=')[0].match(/[A-Za-z_]\w*/g) || []).slice(-1)[0];
      const lhsB = (lines[k].split('=')[0].match(/[A-Za-z_]\w*/g) || []).slice(-1)[0];
      if (idsB.includes(lhsA) || idsA.includes(lhsB) || lhsA === lhsB) continue;
      const nl = lines.slice(); [nl[j], nl[k]] = [nl[k], nl[j]]; return nl.join('\n');
    }
    return null;
  }
}

// --- search: keep-best hill-climb with random restarts from the original ---
let rngState = 0x2545F491;
const rng = () => { rngState = (rngState * 1103515245 + 12345) & 0x7fffffff; return rngState / 0x7fffffff; };
const base = readFileSync(src, 'utf8');
let best = score(base), bestSrc = base;
console.log(`base: ${best}/${want.length}`);
let cur = bestSrc, curScore = best;
for (let it = 0; it < iters && best < want.length; it++) {
  if (it % 400 === 399) { cur = bestSrc; curScore = best; }   // periodic restart from best
  // apply 1-3 compound mutations
  let m = cur;
  const nMut = 1 + Math.floor(rng() * 3);
  for (let q = 0; q < nMut; q++) { const mm = mutate(m, rng); if (mm) m = mm; }
  if (m === cur) continue;
  const s = score(m);
  if (s < 0) continue;
  const T = 3.0 * (1 - it / iters) + 0.05;              // cooling schedule
  if (s >= curScore || rng() < Math.exp((s - curScore) / T)) {
    cur = m; curScore = s;
    if (s > best) {
      // clean up the winner (collapse alias/unused temps) — often reaches exact
      const cm = cleanup(m); const cs = cm === m ? s : score(cm);
      if (cs >= s) { best = cs; bestSrc = cm; if (cs >= curScore) { cur = cm; curScore = cs; } }
      else { best = s; bestSrc = m; }
      console.log(`iter ${it}: ${best}/${want.length}`);
    }
  }
}
console.log(best === want.length ? `\n>>> EXACT MATCH FOUND <<<` : `\nbest ${best}/${want.length}`);
if (best === want.length || process.env.SHOW) { writeFileSync(src.replace(/\.c$/, '.matched.c'), bestSrc); console.log('wrote', src.replace(/\.c$/, '.matched.c')); }
