/* Career_Init__Fv (0x80010000) */
/* C++ (CAREER.CPP). Demo twin; locals from its MAIN.SYM. Clears the career save, stamps its
   version, then fills every level's high-score table with random names from the name list,
   scores stepping down 5000 from the level's base and random skaters. THPS1 has 20 levels and
   no Career_Test call. */
struct SHighScore {
	char Name[4];
	char Skater;
	int Score;
};

struct SCareer {
	int Version;
	char pad4[0xa4 - 4];
	SHighScore HighScore[20][8]; /* 0x0a4 */
	char LastSkater[2];          /* 0x824 */
	char LastDeck[2];
	char LastWheel[2];
	char LastTrucks[2]; /* 0x82a */
	char pad82c[0x9d0 - 0x82c];
};

struct SLevelInfo {
	int BaseScore;
	char pad[120 - 4];
};

extern SCareer DAT_800a6844;
extern char *DAT_800a40b4[];
extern SLevelInfo DAT_800a53dc[];
extern int DAT_800d10f4, DAT_800d10f8;

int Redbook_Rnd(int);
void Options_SetPreferences();

void Career_Init() {
	char *p;
	char **pHighScore;
	int HighScoreCount;

	{
		int i;

		p = (char *)&DAT_800a6844;

		for (i = 0; i < sizeof(SCareer); i++)
			*p++ = 0;
	}

	DAT_800a6844.Version = 0x60299;
	pHighScore = DAT_800a40b4;
	HighScoreCount = 0;

	while (*pHighScore) {
		pHighScore++;
		HighScoreCount++;
	}

	{
		int Level;

		for (Level = 0; Level < 20; Level++) {
			int Score;

			for (Score = 0; Score < 8; Score++) {
				pHighScore = &DAT_800a40b4[Redbook_Rnd(HighScoreCount)];
				DAT_800a6844.HighScore[Level][Score].Name[0] = (*pHighScore)[0];
				DAT_800a6844.HighScore[Level][Score].Name[1] = (*pHighScore)[1];
				DAT_800a6844.HighScore[Level][Score].Name[2] = (*pHighScore)[2];
				DAT_800a6844.HighScore[Level][Score].Score =
				    DAT_800a53dc[Level].BaseScore + (7 - Score) * 5000;
				DAT_800a6844.HighScore[Level][Score].Skater = Redbook_Rnd(10);
			}
		}
	}

	DAT_800d10f4 = 0;
	DAT_800d10f8 = 0;

	{
		int i;

		for (i = 0; i < 2; i++)
			DAT_800a6844.LastTrucks[i] = 1;
	}

	Options_SetPreferences();
}
