/* Competition_EndGameDisplay__Fv (0x80076c4c) */
/* C++ (COMPETITION.CPP). Demo twin (0.98 by opcode); locals from its MAIN.SYM. The end-of-
   competition screen: either the "no medal" text with three bronze placeholders, or the results
   text and the medals won on the ten tracked events, spun in place, then the continue prompt once
   the first medal has settled. */
typedef unsigned char uchar;
typedef unsigned int uint;
enum EMedalType { MEDAL_0 };

class CItem {
  public:
	char pad0[0x48];
	virtual ~CItem();
	virtual void m10();
	virtual void Spin();
};

class CMedal : public CItem {
  public:
	char pad4c[0x160 - 0x4c];
	uint mTimer; /* 0x160 */
};

struct SCompetition {
	char pad0[0xc8];
	CMedal *pMedal[3]; /* 0xc8 */
	char padd4[0x12c - 0xd4];
	int mWaitPrompt; /* 0x12c */
};

struct CBruce {
	char pad0[0x2e8];
	int mSkaterIndex; /* 0x2e8 */
};

struct SCareerRecord {
	uchar Flags[14];
};

extern SCompetition theCompetition;
extern CBruce *GSkater;
extern SCareerRecord GCareer_c[];
extern char DAT_800a3250[], DAT_800a3268[], DAT_800a318c[], DAT_800a3288[], DAT_800a32a8[];
extern char DAT_800a32bc[], DAT_800a32dc[], DAT_800a32f4[], DAT_800a3308[];
extern char *GameText_180[];

void Mess_DeleteAll();
void Mess_SetScale(int);
void Mess_SetRGB(uchar, uchar, uchar, int);
void Front_PrintCentredPrompt(const char *);
CMedal *Medal_Create(EMedalType, int, int, int, int, int);

extern "C" {
	void Mess_SetTextJustify__FUc(int);
	int Mess_DrawText__FiiPCciUiib(int, int, char *, int, int, int, int);
	int FUN_8007401c(void);
}

void Competition_EndGameDisplay() {
	SCompetition *pComp = &theCompetition;

	Mess_DeleteAll();
	Mess_SetScale(256);
	Mess_SetRGB(122, 122, 122, 0);
	Mess_SetTextJustify__FUc(0);

	if (FUN_8007401c()) {
		Mess_DrawText__FiiPCciUiib(256, 40, DAT_800a3250, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 60, DAT_800a3268, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 80, DAT_800a318c, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 180, DAT_800a3288, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 200, DAT_800a32a8, 0, 0, 256, 0);

		if (!pComp->pMedal[0])
			pComp->pMedal[0] = Medal_Create((EMedalType)5, -30, 5, 140, 1536, 3);

		if (!pComp->pMedal[1])
			pComp->pMedal[1] = Medal_Create((EMedalType)5, 0, 5, 140, 1536, 3);

		if (!pComp->pMedal[2])
			pComp->pMedal[2] = Medal_Create((EMedalType)5, 30, 5, 140, 1536, 3);
	} else {
		Mess_DrawText__FiiPCciUiib(256, 40, DAT_800a32bc, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 60, DAT_800a32dc, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 80, DAT_800a32f4, 0, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 180, DAT_800a3308, 0, 0, 256, 0);

		{
			EMedalType m[3];
			int n = 0;
			int i;

			for (i = 0; i < 10; i++) {
				short f = GCareer_c[GSkater->mSkaterIndex].Flags[i];

				if (f & 0x20)
					m[n++] = (EMedalType)5;
				else if (f & 0x40)
					m[n++] = (EMedalType)6;
				else if (f & 0x80)
					m[n++] = (EMedalType)7;
			}

			if (!pComp->pMedal[0])
				pComp->pMedal[0] = Medal_Create(m[0], -30, 5, 140, 1280, 5);

			if (!pComp->pMedal[1])
				pComp->pMedal[1] = Medal_Create(m[1], 0, 5, 140, 1280, 5);

			if (!pComp->pMedal[2])
				pComp->pMedal[2] = Medal_Create(m[2], 30, 5, 140, 1280, 5);
		}
	}

	pComp->pMedal[0]->Spin();
	pComp->pMedal[1]->Spin();
	pComp->pMedal[2]->Spin();

	{
		int Done = 1;

		if (pComp->pMedal[0]) {
			int c = pComp->pMedal[0]->mTimer < 40;

			Done = c == 0;
		}

		if (Done && !pComp->mWaitPrompt)
			Front_PrintCentredPrompt(GameText_180[0]);
	}
}
