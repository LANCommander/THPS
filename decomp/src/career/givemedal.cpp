/* Career_GiveMedal__Fi10EMedalType (0x8001081c) */
/* C++ (CAREER.CPP). Demo twin; locals from its MAIN.SYM. Records a competition medal for the
   current skater on that level (bits 5-7 of the level byte: gold, silver, bronze) and recounts
   the skater's medals over the ten levels that count. */
typedef unsigned char uchar;
enum EMedalType { MEDAL_NONE };

struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex; /* 0x2e8 */
};

struct SLevelInfo {
	int NotCareer;
	char pad4[120 - 4];
};

struct SSkaterCareer {
	char pad0[8];
	uchar NumTapes;  /* 8 */
	uchar NumBronze; /* 9 */
	uchar NumSilver; /* 10 */
	uchar NumGold;   /* 11 */
	uchar Tapes[2];  /* 12 (indexed by level, runs into the next record) */
};

extern CBruce *GSkater;
extern SLevelInfo Levels_c[];
extern SSkaterCareer GCareer[];

void Career_GiveMedal(int Level, EMedalType medal) {
	int g = 0;
	int s = 0;
	int b = 0;

	GCareer[GSkater->mSkaterIndex].Tapes[Level] |= 1 << medal;

	{
		int i;

		for (i = 0; i < 10; i++) {
			if (!Levels_c[i].NotCareer) {
				uchar t = GCareer[GSkater->mSkaterIndex].Tapes[i];

				if (t & 0x20)
					g++;

				if (t & 0x40)
					s++;

				if (t & 0x80)
					b++;
			}
		}
	}

	GCareer[GSkater->mSkaterIndex].NumGold = g;
	GCareer[GSkater->mSkaterIndex].NumSilver = s;
	GCareer[GSkater->mSkaterIndex].NumBronze = b;
}
