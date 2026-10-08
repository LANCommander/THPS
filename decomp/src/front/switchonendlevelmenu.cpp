/* Front_SwitchOnEndLevelMenu__Fv (0x8001a2bc) */
/* C++ (FRONT.CPP). Fuzzy demo twin (0.37; THPS1 drops the checksum debug print); locals from its
   MAIN.SYM. Leaving a level: stop any replay video, pick the end-of-level menu, enter the run's
   score in the level's high-score table (shifting the lower entries down), then set up the menu. */
typedef unsigned char uchar;
typedef unsigned int uint;

struct CBruce {
	char pad0[0x1c];
	CBruce *mpNext; /* 0x01c */
	char pad20[0x2e8 - 0x20];
	uchar mSkaterIndex; /* 0x2e8 */
	char pad2e9[0x8f8 - 0x2e9];
	int mGotSomething; /* 0x8f8 */
	char pad8fc[0x928 - 0x8fc];
	uint mScore; /* 0x928 */
};

struct SVideoInfo {
	int Mode;
	char pad4[0xc0 - 4];
};

struct SLevelInfo {
	char pad0[12];
	int mNoHighScores; /* 12 */
	char pad10[120 - 16];
};

struct SHighScore {
	char Name[4];
	uchar Skater;
	uint Score;
};

struct SCareer {
	char pad0[164];
	SHighScore HighScores[23][8]; /* 164 */
	char pad974[2416 - 164 - 23 * 96];
	char PlayerName[4]; /* 2416 */
};

class FallingTextEffect {
  public:
	void init();
};

extern SVideoInfo GVInfo1;
extern SVideoInfo GVInfo2;
extern SLevelInfo Levels[];
extern SCareer GCareer;
extern FallingTextEffect DAT_800a5b28[];
extern CBruce *MechList;
extern CBruce *GSkater;
extern int GState;
extern int GNumberOfPlayers;
extern int GGame;
extern int GLevel;
extern int GHorseWaitTime;

int Status;
int GHighScoreLineIndex;
int GHighScoreInitialCursorPos;
int GHorseScale;
int GHorseContinue;

void Video_Stop(CBruce *);
void InitStatsSwisch();
int SFX_PlayX(unsigned int, short, int);

extern "C" {
	void CommonSwitchOnMenuCode__Fv(void);
	int FUN_8008b900(char *, const char *, ...);
}

void Front_SwitchOnEndLevelMenu() {
	CBruce *pSkater;
	CBruce *pSkater2;

	GState = 0;

	if (Status == 11 || Status == 13)
		return;

	pSkater = MechList;
	pSkater2 = pSkater->mpNext;

	if (GVInfo1.Mode)
		Video_Stop(pSkater);

	if (pSkater2 && GVInfo2.Mode)
		Video_Stop(pSkater2);

	if (GSkater->mGotSomething && GNumberOfPlayers == 1) {
		SFX_PlayX(19, 8192, 0);

		Status = 11;
	} else if (GGame == 2) {
		Status = 14;
	} else {
		Status = 13;
	}

	if ((GGame == 1 && !Levels[GLevel].mNoHighScores) || GGame == 3) {
		int i;

		GHighScoreLineIndex = -1;
		GHighScoreInitialCursorPos = 0;

		for (i = 0; i < 8; i++) {
			if (pSkater->mScore >= GCareer.HighScores[GLevel][i].Score) {
				int j;

				for (j = 7; j > i; j--) {
					GCareer.HighScores[GLevel][j].Score =
					    GCareer.HighScores[GLevel][j - 1].Score;
					GCareer.HighScores[GLevel][j].Skater =
					    GCareer.HighScores[GLevel][j - 1].Skater;

					{
						/* the counter is initialised between the two pointers (retail's t0/a3 order) */
						char *d = GCareer.HighScores[GLevel][j].Name;
						int k = 3;
						char *s = GCareer.HighScores[GLevel][j - 1].Name;

						for (; k != -1; k--)
							*d++ = *s++;
					}
				}

				GCareer.HighScores[GLevel][i].Score = pSkater->mScore;
				GCareer.HighScores[GLevel][i].Skater = GSkater->mSkaterIndex;
				FUN_8008b900(GCareer.HighScores[GLevel][i].Name,
				             GCareer.PlayerName);

				GHighScoreLineIndex = i;
				i = 8;
			}
		}
	}

	if (GGame == 7) {
		DAT_800a5b28[0].init();

		GHorseScale = 0;
		GHorseWaitTime = 45;
		GHorseContinue = 0;
	}

	CommonSwitchOnMenuCode__Fv();
	InitStatsSwisch();
}
