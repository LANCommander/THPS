/* Career_Got__Fi (0x800106e0) */
/* C++ (CAREER.CPP), next to Career_GiveTape. Whether the current skater has goal (tape) `Goal` of
   the current level. */
typedef unsigned char uchar;

struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex; /* 0x2e8 */
};

struct SSkaterCareer {
	char pad0[8];
	uchar NumTapes; /* 8 */
	char pad9[3];
	uchar Tapes[2]; /* 12 (indexed by level, runs into the next record) */
};

extern CBruce *DAT_800d17c8;
extern SSkaterCareer DAT_800a6844[];
extern int DAT_800d1e28;

extern "C" int Career_Got__Fi(int Goal) {
	return (DAT_800a6844[DAT_800d17c8->mSkaterIndex].Tapes[DAT_800d1e28] >> Goal) & 1;
}
