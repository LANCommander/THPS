/* Career_GiveTape__Fii (0x80010724) */
/* C++ (CAREER.CPP). Demo twin; locals from its MAIN.SYM. Marks a level goal (tape) as got for the
   current skater, recounts the skater's goals over the ten levels that count, and bumps the
   skater's goal-got counter. */
typedef unsigned char uchar;

struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex; /* 0x2e8 */
	char pad2ec[0x8f8 - 0x2ec];
	int mGotSomething; /* 0x8f8 */
};

struct SLevelInfo {
	int NotCareer;
	char pad4[120 - 4];
};

struct SSkaterCareer {
	char pad0[8];
	uchar NumTapes; /* 8 */
	char pad9[3];
	uchar Tapes[2]; /* 12 (indexed by level, runs into the next record) */
};

extern CBruce *DAT_800d17c8;
extern SLevelInfo DAT_800a53a4[];
extern SSkaterCareer DAT_800a6844[];

void Career_GiveTape(int Level, int Goal) {
	int t = 0;

	DAT_800a6844[DAT_800d17c8->mSkaterIndex].Tapes[Level] |= 1 << Goal;

	{
		int j;

		for (j = 0; j < 10; j++) {
			int i;

			for (i = 0; i < 5; i++) {
				if (!DAT_800a53a4[j].NotCareer &&
				    ((DAT_800a6844[DAT_800d17c8->mSkaterIndex].Tapes[j] >> i) & 1))
					t++;
			}
		}
	}

	DAT_800a6844[DAT_800d17c8->mSkaterIndex].NumTapes = t;
	DAT_800d17c8->mGotSomething++;
}
