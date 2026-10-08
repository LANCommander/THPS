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

extern CBruce *GSkater;
extern SSkaterCareer GCareer[];
extern int GLevel;

extern "C" int Career_Got__Fi(int Goal) {
	return (GCareer[GSkater->mSkaterIndex].Tapes[GLevel] >> Goal) & 1;
}
