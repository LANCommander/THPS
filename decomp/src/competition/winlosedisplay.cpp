/* Competition_WinLoseDisplay__Fv (0x80075964) flags=-fstructure-noalias */
/* C++ (COMPETITION.CPP). Fuzzy demo twin (0.98); locals from its MAIN.SYM. End of a competition:
   simulates the AI skaters' remaining runs (base score by skill, a random dip, the judges'
   biases; best two of three runs count), sorts the standings, then shows our result (a medal
   for the top three, else the podium and our place), the medal unlock text and the prompt. */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
enum EMedalType { MEDAL_0 };

class CItem {
  public:
	char pad0[8];
	int mY; /* 0x08 */
	char padc[0x48 - 0xc];
	virtual ~CItem();
	virtual void Virtual2();
	virtual void AI();
};

class CBody : public CItem {
  public:
	char pad4c[0x14c - 0x4c];
	int m14C; /* 0x14c */
	char pad150[0x156 - 0x150];
	ushort m156; /* 0x156 */
	ushort m158; /* 0x158 */
	char pad15a[0x160 - 0x15a];
	uint mTimer; /* 0x160 */
};

struct SBias {
	uchar Plus;
	uchar PlusAmount;
	uchar Minus;
	uchar MinusAmount;
	char pad[4];
};

struct SCompetition {
	char pad0[4];
	uchar SkaterId[20]; /* 0x04 */
	int SoundDone;      /* 0x18 */
	char pad1c[0x2c - 0x1c];
	SBias Bias[5]; /* 0x2c */
	char pad54[0x5c - 0x54];
	uchar Order[20];      /* 0x5c */
	ushort Scores[10][3]; /* 0x70 */
	ushort Best[10];      /* 0xac */
	uchar Run;            /* 0xc0 */
	char padc1[0xc4 - 0xc1];
	int MedalMask; /* 0xc4 */
	CBody *pMedal; /* 0xc8 */
	char padcc[0x128 - 0xcc];
	int Player;   /* 0x128 */
	int NoPrompt; /* 0x12c */
};

struct SSkater {
	char pad0[44];
	char *pName; /* 44 */
	char pad30[340 - 48];
};

struct SCareer {
	char pad0[12];
	uchar Medals[0x984 - 12]; /* 12, [player * 14 + level] */
	int Total[2];             /* 0x984 */
};

struct SGame {
	char pad0[0x2e8];
	int Player; /* 0x2e8 */
};

extern SCompetition DAT_800c0fdc;
extern char *DAT_800c0fb8[9];
extern SSkater DAT_800a44fc[];
extern SCareer DAT_800a6844;
extern SGame *DAT_800d17c8;
extern int DAT_800d1e28;
extern char *DAT_800a5edc[];
extern char DAT_800a3328[];
extern char DAT_800a333c[];
extern char DAT_800a3350[];
extern char DAT_800a3364[];
extern char DAT_800a3370[];
extern char DAT_800a3380[];
extern char DAT_800a3390[];
extern char DAT_800d1fcc[];

ushort DAT_800d1fc2;
ushort DAT_800d1fc4;
ushort DAT_800d1fc6;
ushort DAT_800d1fc8;

void Mess_DeleteAll(void);
void Mess_SetScale(int);
void Mess_SetRGB(uchar, uchar, uchar, int);
int Redbook_Rnd(int);
CBody *Medal_Create(EMedalType, int, int, int, int, int);
void Front_PrintCentredPrompt(const char *);

extern "C" {
	int FUN_8001e114(int, int, char *, int, int, int, int);
	void FUN_8001081c(int, int);
	int FUN_8004b250(int, short, int);
	int FUN_8008b900(char *, const char *, ...);
}

void Competition_WinLoseDisplay() {
	int our_placing;
	char buf[40];
	SCompetition *c = &DAT_800c0fdc;

	Mess_DeleteAll();

	while (c->Run < 3) {
		uchar i;
		int b;

		/* no for-increment: g++ puts a deleted note after a for's continue label, which stops
		   reorg predicting the skip as taken (retail fills its delay slot from the target) */
		i = (uchar)-1;

		while (++i < 10) {
			ushort base;
			uchar j;

			if (i == c->Player)
				continue;

			if (c->Order[i] == 0)
				base = DAT_800d1fc2;
			else if (c->Order[i] == 1)
				base = DAT_800d1fc4;
			else if (c->Order[i] == 2)
				base = DAT_800d1fc6;
			else
				base = Redbook_Rnd(DAT_800d1fc6 - DAT_800d1fc8) + DAT_800d1fc8;

			base -= Redbook_Rnd(18);

			for (j = 0; j < 5; j++) {
				SCompetition *p = (SCompetition *)((char *)c + j * sizeof(SBias));

				if (i == p->Bias[0].Plus)
					base += p->Bias[0].PlusAmount;

				if (i == p->Bias[0].Minus)
					base -= p->Bias[0].MinusAmount;
			}

			c->Scores[i][c->Run] = base;
		}

		c->Run++;

		for (b = 0; b < 10; b++) {
			uint score0 = c->Scores[b][0];
			uint score1 = c->Scores[b][1];
			uint score2 = c->Scores[b][2];

			if (score0 < score1 && score0 < score2)
				c->Best[b] = score1 + score2;
			else if (score1 < score0 && score1 < score2)
				c->Best[b] = score0 + score2;
			else
				c->Best[b] = score0 + score1;
		}
	}

	{
		int i;

		for (i = 0; i < 10; i++)
			c->Order[i] = i;
	}

	{
		int i;

		for (i = 1; i < 10; i++) {
			int j = i;

			while (c->Best[c->Order[j]] > c->Best[c->Order[j - 1]]) {
				uchar t = c->Order[j];
				uchar u = c->Order[j - 1];

				c->Order[j - 1] = t;
				c->Order[j] = u;

				if (--j <= 0)
					break;
			}
		}
	}

	Mess_SetScale(256);
	Mess_SetRGB(122, 122, 122, 0);

	{
		int i;

		for (i = 0; i < 10; i++)
			if (c->Order[i] == c->Player)
				our_placing = i;
	}

	switch (our_placing) {
		case 0:
			FUN_8001e114(256, 40, DAT_800a3328, 0, 0, 256, 0);

			if (!c->pMedal) {
				FUN_8001081c(DAT_800d1e28, 5);

				c->pMedal = Medal_Create((EMedalType)5, 0, -5, 140, 2048, 10);
			}

			if (!c->SoundDone) {
				FUN_8004b250(45, 0x2000, 0);
				FUN_8004b250(48, 0x2000, 0);

				c->SoundDone = 1;
			}

			break;
		case 1:
			FUN_8001e114(256, 40, DAT_800a333c, 0, 0, 256, 0);

			if (!c->pMedal) {
				FUN_8001081c(DAT_800d1e28, 6);

				c->pMedal = Medal_Create((EMedalType)6, 0, -5, 140, 2048, 10);
			}

			if (!c->SoundDone) {
				FUN_8004b250(48, 0x2000, 0);

				c->SoundDone = 1;
			}

			break;
		case 2:
			FUN_8001e114(256, 40, DAT_800a3350, 0, 0, 256, 0);

			if (!c->pMedal) {
				FUN_8001081c(DAT_800d1e28, 7);

				c->pMedal = Medal_Create((EMedalType)7, 0, -5, 140, 2048, 10);
			}

			if (!c->SoundDone) {
				FUN_8004b250(45, 0x2000, 0);

				c->SoundDone = 1;
			}

			break;
		default: {
			int first;
			int second;
			int third;

			if (!c->SoundDone) {
				FUN_8004b250(47, 0x2000, 0);

				c->SoundDone = 1;
			}

			FUN_8001e114(256, 40, DAT_800a3364, 0, 0, 256, 0);

			{
				int i;

				for (i = 0; i < 10; i++) {
					if (c->Order[0] == i)
						first = i;

					if (c->Order[11] == i)
						second = i;

					if (c->Order[12] == i)
						third = i;
				}
			}

			Mess_SetRGB(182, 132, 36, 0);
			Mess_SetScale(160);
			FUN_8008b900(buf, DAT_800a3370, DAT_800a44fc[c->SkaterId[first]].pName);
			FUN_8001e114(256, 60, buf, 0, 0, 256, 0);
			FUN_8008b900(buf, DAT_800a3380, DAT_800a44fc[c->SkaterId[second]].pName);
			FUN_8001e114(256, 70, buf, 0, 0, 256, 0);
			FUN_8008b900(buf, DAT_800a3390, DAT_800a44fc[c->SkaterId[third]].pName);
			FUN_8001e114(256, 80, buf, 0, 0, 256, 0);
			Mess_SetRGB(122, 122, 122, 0);
			FUN_8008b900(buf, DAT_800d1fcc, our_placing + 1);
			Mess_SetScale(384);
			FUN_8001e114(256, 120, DAT_800a44fc[c->SkaterId[c->Player]].pName, 0, 0, 256, 0);
			FUN_8001e114(256, 150, buf, 0, 0, 256, 0);
			break;
		}
	}

	if (c->pMedal) {
		c->pMedal->AI();

		c->MedalMask = 0;

		if (DAT_800a6844.Medals[DAT_800d1e28 + DAT_800d17c8->Player * 14] & 0xe0)
			c->MedalMask = 1 << DAT_800d1e28;

		Mess_SetScale(256);
		Mess_SetRGB(122, 122, 122, 0);

		if (DAT_800a6844.Total[DAT_800d17c8->Player] == 328) {
			c->pMedal->m156 = c->pMedal->m158 = 2;
			c->pMedal->mY = c->pMedal->m14C - 0x5000;

			if (DAT_800c0fb8[6])
				FUN_8001e114(256, 155, DAT_800c0fb8[6], 0, 0, 256, 0);

			if (DAT_800c0fb8[7])
				FUN_8001e114(256, 175, DAT_800c0fb8[7], 0, 0, 256, 0);

			if (DAT_800c0fb8[8])
				FUN_8001e114(256, 195, DAT_800c0fb8[8], 0, 0, 256, 0);
		} else {
			switch ((DAT_800a6844.Total[DAT_800d17c8->Player] & c->MedalMask) ^ c->MedalMask) {
				case 8:
					if (DAT_800c0fb8[0])
						FUN_8001e114(256, 155, DAT_800c0fb8[0], 0, 0, 256, 0);

					if (DAT_800c0fb8[1])
						FUN_8001e114(256, 175, DAT_800c0fb8[1], 0, 0, 256, 0);

					if (DAT_800c0fb8[2])
						FUN_8001e114(256, 195, DAT_800c0fb8[2], 0, 0, 256, 0);

					break;
				case 64:
					if (DAT_800c0fb8[3])
						FUN_8001e114(256, 155, DAT_800c0fb8[3], 0, 0, 256, 0);

					if (DAT_800c0fb8[4])
						FUN_8001e114(256, 175, DAT_800c0fb8[4], 0, 0, 256, 0);

					if (DAT_800c0fb8[5])
						FUN_8001e114(256, 195, DAT_800c0fb8[5], 0, 0, 256, 0);

					break;
				case 256:
					c->pMedal->m156 = c->pMedal->m158 = 2;
					c->pMedal->mY = c->pMedal->m14C - 0x5000;

					if (DAT_800c0fb8[6])
						FUN_8001e114(256, 155, DAT_800c0fb8[6], 0, 0, 256, 0);

					if (DAT_800c0fb8[7])
						FUN_8001e114(256, 175, DAT_800c0fb8[7], 0, 0, 256, 0);

					if (DAT_800c0fb8[8])
						FUN_8001e114(256, 195, DAT_800c0fb8[8], 0, 0, 256, 0);

					break;
			}
		}

		{
			int show = 1;

			if (c->pMedal && c->pMedal->mTimer < 40)
				show = 0;

			if (show && !c->NoPrompt)
				Front_PrintCentredPrompt(DAT_800a5edc[0]);
		}
	} else {
		if (!c->NoPrompt)
			Front_PrintCentredPrompt(DAT_800a5edc[0]);
	}
}
