// Shared compile helpers for the Node matchers: optional CPPPSX preprocessing (for sources that
// #include the Psy-Q SDK headers, e.g. libgte.h / inline_c.h) and the DMPSX GTE-command fixup.
import { readFileSync, mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';

export const CC1 = process.env.CC1 || 'D:/Tools/psyq4.5/CC1PSX.EXE';
const CPP = process.env.CPP || 'D:/Tools/psyq4.5/CPPPSX.EXE';
const INC = process.env.PSYQ_INC || 'D:/Tools/psyq4.5/include';
// what CCPSX hands cpp for C on the PSX target
const CPP_DEFS = ['-undef', '-D__GNUC__=2', '-D__OPTIMIZE__', '-Dmips', '-D__mips__', '-D__psx__', '-D_LANGUAGE_C'];

// cc1 has no preprocessor (not even comment stripping), so always run CPPPSX first, as CCPSX does.
export function cc1(cfile, sfile, opt = '-O2', g = 0) {
  const input = sfile + '.i';
  mkdirSync('build', { recursive: true });
  execFileSync(CPP, [...CPP_DEFS, '-I', INC, cfile, input], { stdio: 'ignore' });
  execFileSync(CC1, [input, '-quiet', ...opt.split(' '), `-G${g}`, '-o', sfile], { stdio: 'ignore' });
}

// INLINE_C.H emits GTE commands as `.word (n<<6)|0x3f` placeholders that Sony's DMPSX.EXE patches
// into real cop2 words post-assembly; apply the same table (tools/dmpsx_table.json, from
// gen_dmpsx_table.py) to the assembled words.
const DMPSX = new Map(Object.entries(JSON.parse(readFileSync(new URL('./dmpsx_table.json', import.meta.url), 'utf8')))
  .map(([k, v]) => [parseInt(k, 16), parseInt(v, 16) >>> 0]));
export const dmpsx = words => words.map(w => DMPSX.get(w) ?? w);
