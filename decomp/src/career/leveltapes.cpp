/* Career_LevelTapes__Fi (0x80010944) */
/* C++ (CAREER.CPP). Demo twin; locals from its MAIN.SYM. Counts the current skater's tapes (goals)
   on the current level; THPS1 ignores the Level argument. */
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

int Career_LevelTapes(int Level) {
	int t = 0;

	{
		int i;

		for (i = 0; i < 5; i++)
			if ((DAT_800a6844[DAT_800d17c8->mSkaterIndex].Tapes[DAT_800d1e28] >> i) & 1)
				t++;
	}

	return t;
}
