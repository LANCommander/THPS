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

extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern SLevelInfo DAT_800a5398[];
extern SCareer DAT_800a6844;
extern FallingTextEffect DAT_800a5b28[];
extern CBruce *DAT_800d19a4;
extern CBruce *DAT_800d17c8;
extern int DAT_800d1784;
extern int DAT_800d1780;
extern int DAT_800d16a4;
extern int DAT_800d1e28;
extern int DAT_800d17bc;

int DAT_800d13e8;
int DAT_800d13dc;
int DAT_800d13e0;
int DAT_800d14f8;
int DAT_800d13c4;

void Video_Stop(CBruce *);
void InitStatsSwisch();
int SFX_PlayX(unsigned int, short, int);

extern "C" {
	void FUN_8001a128(void);
	int FUN_8008b900(char *, const char *, ...);
}

void Front_SwitchOnEndLevelMenu() {
	CBruce *pSkater;
	CBruce *pSkater2;

	DAT_800d1784 = 0;

	if (DAT_800d13e8 == 11 || DAT_800d13e8 == 13)
		return;

	pSkater = DAT_800d19a4;
	pSkater2 = pSkater->mpNext;

	if (DAT_800bf318.Mode)
		Video_Stop(pSkater);

	if (pSkater2 && DAT_800bf3d8.Mode)
		Video_Stop(pSkater2);

	if (DAT_800d17c8->mGotSomething && DAT_800d1780 == 1) {
		SFX_PlayX(19, 8192, 0);

		DAT_800d13e8 = 11;
	} else if (DAT_800d16a4 == 2) {
		DAT_800d13e8 = 14;
	} else {
		DAT_800d13e8 = 13;
	}

	if ((DAT_800d16a4 == 1 && !DAT_800a5398[DAT_800d1e28].mNoHighScores) || DAT_800d16a4 == 3) {
		int i;

		DAT_800d13dc = -1;
		DAT_800d13e0 = 0;

		for (i = 0; i < 8; i++) {
			if (pSkater->mScore >= DAT_800a6844.HighScores[DAT_800d1e28][i].Score) {
				int j;

				for (j = 7; j > i; j--) {
					DAT_800a6844.HighScores[DAT_800d1e28][j].Score =
					    DAT_800a6844.HighScores[DAT_800d1e28][j - 1].Score;
					DAT_800a6844.HighScores[DAT_800d1e28][j].Skater =
					    DAT_800a6844.HighScores[DAT_800d1e28][j - 1].Skater;

					{
						/* the counter is initialised between the two pointers (retail's t0/a3 order) */
						char *d = DAT_800a6844.HighScores[DAT_800d1e28][j].Name;
						int k = 3;
						char *s = DAT_800a6844.HighScores[DAT_800d1e28][j - 1].Name;

						for (; k != -1; k--)
							*d++ = *s++;
					}
				}

				DAT_800a6844.HighScores[DAT_800d1e28][i].Score = pSkater->mScore;
				DAT_800a6844.HighScores[DAT_800d1e28][i].Skater = DAT_800d17c8->mSkaterIndex;
				FUN_8008b900(DAT_800a6844.HighScores[DAT_800d1e28][i].Name,
				             DAT_800a6844.PlayerName);

				DAT_800d13dc = i;
				i = 8;
			}
		}
	}

	if (DAT_800d16a4 == 7) {
		DAT_800a5b28[0].init();

		DAT_800d14f8 = 0;
		DAT_800d17bc = 45;
		DAT_800d13c4 = 0;
	}

	FUN_8001a128();
	InitStatsSwisch();
}
