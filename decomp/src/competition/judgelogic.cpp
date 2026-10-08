/* Competition_JudgeLogic__Fv (0x80074350) */
/* C++ (COMPETITION.CPP). Demo twin (0.99); locals from its MAIN.SYM. On the first frame of the
   judging, each of the five judges scores the run: the skater's points against the level's three
   medal thresholds pick a band (interpolated between the band scores), minus a penalty scaled by
   a skater counter (+0x930),
   a random dip, and the judge's bias for or against our skater. The run's score is the average of
   the three middle judges. Gold/Silver/Bronze are read into locals (not in the SYM) and each band
   formula is two statements, as in the old draft; the shapes decide register use and cross-jumping. */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

class CClass {
  public:
	virtual ~CClass();
};

class CJudge : public CClass {
  public:
	uchar mProPlayer;
	uchar mProBias;
	uchar mConPlayer;
	uchar mConBias;
};

class CCompetition : public CClass {
  public:
	uchar mCompetitorList[10];
	uint mJudgeTimer; /* 0x10 */
	uint mLadderTimer;
	int mWinLoseCheer;
	uchar mLastLadderEntry;
	int mJudgeFullyDisplayed; /* 0x20 */
	int mLadderFullyDisplayed;
	CJudge mJudges[5];     /* 0x28 */
	short mJudgesScore[5]; /* 0x50 */
	uchar mHighScore;      /* 0x5a */
	uchar mLowScore;       /* 0x5b */
	uchar mPlacing[10];
	uchar mOrdering[10];
	ushort mScore[10][3]; /* 0x70 */
	ushort mTotalScore[10];
	uchar mCurrentHeat; /* 0xc0 */
	char padc1[0x128 - 0xc1];
	int our_skater_num; /* 0x128 */
	int mFading;
};

struct SLevel {
	char pad0[0x18];
	uint Gold;   /* 0x18 */
	uint Silver; /* 0x1c */
	uint Bronze; /* 0x20 */
	char pad24[120 - 0x24];
};

class CBruce {
  public:
	char pad0[0x928];
	uint mScore; /* 0x928 */
	char pad92c[0x930 - 0x92c];
	ushort m930; /* 0x930 */
};

extern CCompetition DAT_800c0fdc;
extern SLevel DAT_800a5398[];
extern CBruce *DAT_800d19a4;
extern int DAT_800d1e28;

ushort DAT_800d1fc0;
ushort DAT_800d1fc2;
ushort DAT_800d1fc4;
ushort DAT_800d1fc6;

int Redbook_Rnd(int);

void Competition_JudgeLogic() {
	CCompetition *c = &DAT_800c0fdc;

	if (!c->mJudgeTimer) {
		CBruce *pSkater;
		uint temp;
		uint score;
		int average_score;

		pSkater = DAT_800d19a4;
		c->mJudgeFullyDisplayed = 0;
		score = pSkater->mScore;

		{
			int i;

			for (i = 0; i < 5; i++) {
				uint Gold = DAT_800a5398[DAT_800d1e28].Gold;

				if (Gold * 2 < score) {
					temp = ((score - Gold * 2) << 12) / (Gold * 3);
					temp = ((1000 - DAT_800d1fc0) * temp) >> 12;
					temp += DAT_800d1fc0;
				} else if (Gold < score) {
					temp = ((score - Gold) << 12) / Gold;
					temp = ((DAT_800d1fc0 - DAT_800d1fc2) * temp) >> 12;
					temp += DAT_800d1fc2;
				} else {
					uint Silver = DAT_800a5398[DAT_800d1e28].Silver;

					if (Silver < score) {
						temp = ((score - Silver) << 12) / (Gold - Silver);
						temp = ((DAT_800d1fc2 - DAT_800d1fc4) * temp) >> 12;
						temp += DAT_800d1fc4;
					} else {
						uint Bronze = DAT_800a5398[DAT_800d1e28].Bronze;

						if (Bronze < score) {
							temp = ((score - Bronze) << 12) / (Silver - Bronze);
							temp = ((DAT_800d1fc4 - DAT_800d1fc6) * temp) >> 12;
							temp += DAT_800d1fc6;
						} else {
							temp = (score << 12) / Bronze;
							temp = ((DAT_800d1fc6 - 300) * temp) >> 12;
							temp += 300;
						}
					}
				}

				c->mJudgesScore[i] = temp;
				temp = pSkater->m930 * (Redbook_Rnd(15) + 10);

				if (temp > 300)
					temp = 300;

				if (temp >= c->mJudgesScore[i])
					c->mJudgesScore[i] = 0;
				else
					c->mJudgesScore[i] -= temp;

				c->mJudgesScore[i] -= Redbook_Rnd(8);

				if (c->mJudges[i].mProPlayer == c->our_skater_num)
					c->mJudgesScore[i] += c->mJudges[i].mProBias;

				if (c->mJudges[i].mConPlayer == c->our_skater_num &&
				    c->mJudgesScore[i] > c->mJudges[i].mConBias)
					c->mJudgesScore[i] -= c->mJudges[i].mConBias;

				if (c->mJudgesScore[i] < 0)
					c->mJudgesScore[i] = 0;

				if (c->mJudgesScore[i] >= 1000)
					c->mJudgesScore[i] = 999;

				if (!score)
					c->mJudgesScore[i] = 0;
			}
		}

		c->mLowScore = 0;

		{
			int i;

			for (i = 0; i < 5; i++)
				if (c->mJudgesScore[i] < c->mJudgesScore[c->mLowScore])
					c->mLowScore = i;
		}

		if (!c->mLowScore)
			c->mHighScore = 1;
		else
			c->mHighScore = 0;

		{
			int i;

			for (i = 0; i < 5; i++)
				if (i != c->mLowScore && c->mJudgesScore[c->mHighScore] < c->mJudgesScore[i])
					c->mHighScore = i;
		}

		average_score = 0;

		{
			int i;

			for (i = 0; i < 5; i++)
				if (i != c->mLowScore && i != c->mHighScore)
					average_score += c->mJudgesScore[i];
		}

		average_score /= 3;
		c->mScore[c->our_skater_num][c->mCurrentHeat] = average_score;
	}

	c->mJudgeTimer++;
}
