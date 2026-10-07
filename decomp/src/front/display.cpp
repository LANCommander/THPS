/* Front_Display__Fv (0x80017d70) flags=-fstructure-noalias */
/* C++ (FRONT.CPP). Fuzzy demo twin (0.55); locals and statics from its MAIN.SYM. Draws whatever
   the front end is showing, by DAT_800d13e8 (the current screen): the pause and quit menus, the
   tapes-got screen (creating the spinning tapes the first time round), the yes/no menus, the
   name entry, the H.O.R.S.E. turn screens, the level's high-score table and the end-of-run
   statistics (career totals, two-player result, graffiti tallies or the H.O.R.S.E. letters).
   H.O.R.S.E. case: `Line = 0;` before the player-colour test is retail's dead `addu s2,zero,zero`
   in that bne's delay slot (Line is the SYM's function-wide s2 row counter); the second player's
   rows use Line++ * 24 + 80. Residue: the first of those rows isn't folded to 80 (2 words), and
   the NO SCORE tail cross-jumps from the call where retail shares only `xori; sw`. */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

class CClass {
public:
	virtual ~CClass();
};
class CMenu : public CClass {
public:
	uchar mJustification;
	uchar mRep;
	uchar mLine;
	uchar mHasCursor;
	uchar mCursorLine;
	uchar mNumLines;
	int mX;
	int mY;
	void Display();
	void EntryOn(const char *);
	void EntryOff(const char *);
	void CentreY();
};
class CTape {
public:
	char pad0[0x140];
	int mSessionTapeNum;       /* 0x140 */
	int mTapeNum;              /* 0x144 */
	void AI(int tape_no);
	static int DisplayTitle();
	static int DisplayContinueButton();
};
class CBruce {
public:
	char pad0[0x1f0];
	int mGraffitiCount;        /* 0x1f0 */
	char pad1f4[0x2e8 - 0x1f4];
	int mSkaterIndex;          /* 0x2e8 */
	char pad2ec[0x8f8 - 0x2ec];
	int mNumTapes;             /* 0x8f8 */
	char pad8fc[0x928 - 0x8fc];
	uint mScore;               /* 0x928 */
	char pad92c[0x92e - 0x92c];
	ushort mTricksLanded;      /* 0x92e */
	ushort mBails;             /* 0x930 */
	ushort mBestComboTricks;   /* 0x932 */
	int mBestComboScore;       /* 0x934 */
	char mBestCombo1[100];     /* 0x938 */
	char mBestCombo2[100];     /* 0x99c */
	char mBestCombo3[100];     /* 0xa00 */
	uint mHorseScore;          /* 0xa64 */
};
struct STrig {
	short s, c;
};
struct SHighScore {
	char Name[4];
	uchar Skater;
	uint Score;
};
struct SCareer {
	char pad0[8];
	uchar LevelTapes[11][14];  /* 8 */
	char pad9e[164 - 8 - 154];
	SHighScore HighScores[23][8];  /* 164 */
	char pad944[0x9bc - 164 - 23 * 96];
	int HorseLength;           /* 0x9bc */
	char HorseWord[16];        /* 0x9c0 */
};
struct SLevelInfo {
	char *pName;
	char pad4[120 - 4];
};
struct SSkaterInfo {
	char *pName;
	char pad[0x154 - 4];
};

extern int DAT_800d1714;
extern int DAT_800d16e4;
extern int DAT_800d1780;
extern int DAT_800d16a4;
extern int DAT_800d1e28;
extern int DAT_800d1100;
extern int DAT_800d17b8;
extern int DAT_800d179c;
extern int DAT_800d17a0;
extern int DAT_800d17a4;
extern int DAT_800d17ac;
extern int DAT_800d17b0[2];
extern int DAT_800d17bc;
extern int DAT_800d19dc;
extern int DAT_800d1954, DAT_800d1958, DAT_800d195c, DAT_800d1960;
extern int DAT_800d1964, DAT_800d1968, DAT_800d196c, DAT_800d1970;
extern CBruce *DAT_800d17c8;
extern CBruce *DAT_800d17cc;
extern CBruce *DAT_800d19a4;
extern STrig DAT_800c9670[1];
extern char *DAT_800a5d5c[];
extern CTape *DAT_800a5b14[];
extern char DAT_800a7204[];
extern int DAT_800a5cec[];
extern int DAT_800a5d0c[];
extern SCareer DAT_800a6844;
extern SLevelInfo DAT_800a5398[];
extern SSkaterInfo DAT_800a4528[];
extern char DAT_800a5b28[];
extern char DAT_8009e3d4[], DAT_8009e3e8[], DAT_8009e3fc[], DAT_8009e40c[];
extern char DAT_8009e41c[], DAT_8009e428[], DAT_8009e434[], DAT_8009e440[], DAT_8009e450[];
extern char DAT_8009e460[], DAT_8009e470[], DAT_8009e484[], DAT_8009e494[];
extern char DAT_8009e4a4[], DAT_8009e4b0[], DAT_8009e4bc[], DAT_8009e4cc[];
extern char DAT_800d14ac[], DAT_800d14b0[], DAT_800d14b4[], DAT_800d14b8[];
extern char DAT_800d14bc[], DAT_800d14c0[], DAT_800d14c8[], DAT_800d14d0[];

int DAT_800d13e8;
int DAT_800d140c;
int DAT_800d1410;
int DAT_800d1414;
CMenu *DAT_800d1474;
CMenu *DAT_800d1478;
CMenu *DAT_800d1428;
CMenu *DAT_800d142c;
CMenu *DAT_800d1430;
CMenu *DAT_800d1434;
CMenu *DAT_800d1438;
CMenu *DAT_800d143c;
CMenu *DAT_800d1440;
int DAT_800d13d8;
int DAT_800d1514;
int DAT_800d13dc;
int DAT_800d13e0;
int DAT_800d13c4;
int DAT_800d14f4;
int DAT_800d14f8;
int DAT_800d14fc;
int DAT_800d1500;
int DAT_800d1504;
int DAT_800d1508;
int DAT_800d150c[2];

void Mess_SetScale(int);
void Mess_SetRGB(uchar, uchar, uchar, int);
void Front_MemCardDisplay();
void Front_PrintSelect();
void Front_PrintGoBackSelect();
void Front_PrintCentredPrompt(const char *);
void Horse_DisplayWords(int *);
void Graffiti_Stats(CBruce *, int, int, int, int, int, int, int, int, int);
CTape *Tape_Create(int, int, int, int, int, int, int, int);
int SFX_PlayX(unsigned int, short, int);
int Career_LevelTapes(int);
void Competition_JudgeDisplay();
void Competition_LadderDisplay();
void Competition_WinLoseDisplay();
void Competition_EndGameDisplay();
extern "C" {
void FUN_8006c610(int, int, int, int, uchar, uchar, uchar, int);
void FUN_800785c4(void);
void FUN_80017898(void);
void FUN_8001d250(int);
int FUN_8001e114(int, int, char *, int, int, int, int);
int FUN_8008b900(char *, const char *, ...);
void FUN_8001e07c(char *);
void FUN_8001e0a4(char *, int);
void FUN_8001e0f8(char *, short);
ushort FUN_8001e108(char *);
}

void Front_Display()
{
	CBruce *pMan;
	static char Score1[20];
	static char Score2[20];
	static char Tapes[5];
	static char Tricks[8];
	static char Bails[8];
	static char BestCombo[40];
	int Line;

	if (DAT_800d1714)
		FUN_8006c610(19, 190, 194, 42, 0, 0, 0, 0);
	if (DAT_800d140c)
		FUN_800785c4();
	FUN_8001d250(0);
	Mess_SetScale(256);
	switch (DAT_800d13e8) {
	case 18:
		Front_MemCardDisplay();
		break;
	case 1:
		FUN_80017898();
		if (DAT_800d1714)
			Front_PrintSelect();
		else
			Front_PrintGoBackSelect();
		if (DAT_800d1410) {
			DAT_800d1410 -= 2;
			DAT_800d1414 += 690;
			if (DAT_800d1410 < 0) {
				DAT_800d1410 = 0;
				DAT_800d1414 = 0;
			}
		}
		DAT_800d1474->mX = DAT_800d1410 * (DAT_800c9670 + (DAT_800d1414 & 4095))->c / 4096 + 256;
		DAT_800d1474->Display();
		break;
	case 2:
		if (DAT_800d1478)
			DAT_800d1478->Display();
		break;
	case 3:
		FUN_80017898();
		Front_PrintGoBackSelect();
		Mess_SetRGB(150, 100, 25, 0);
		FUN_8001e114(256, 95, DAT_800a5d5c[111], 0, 0, 256, 0);
		DAT_800d1428->mY = 135;
		DAT_800d1428->Display();
		break;
	case 4:
		FUN_80017898();
		Mess_SetRGB(180, 10, 10, 0);
		if ((DAT_800d16e4 / 10) & 1)
			FUN_8001e114(256, 184, DAT_800a5d5c[99], 0, 0, 256, 0);
		break;
	case 11:
		{
			int NumTapes = DAT_800d17c8->mNumTapes;
			if (!DAT_800a5b14[0]) {
				SFX_PlayX(19, 8192, 0);
				switch (NumTapes) {
				case 1:
					DAT_800a5b14[0] = Tape_Create(0, 0, 140, 2304, -80, 0, 140, 1024);
					break;
				case 2:
					DAT_800a5b14[0] = Tape_Create(-50, 0, 140, 2176, -80, -25, 140, 1024);
					DAT_800a5b14[1] = Tape_Create(50, 0, 140, 2176, -80, 25, 140, 1024);
					break;
				case 3:
					DAT_800a5b14[0] = Tape_Create(0, 0, 140, 2304, -80, -40, 140, 1024);
					DAT_800a5b14[1] = Tape_Create(-60, 0, 140, 1792, -80, 0, 140, 1024);
					DAT_800a5b14[2] = Tape_Create(60, 0, 140, 1792, -80, 40, 140, 1024);
					break;
				case 4:
					DAT_800a5b14[0] = Tape_Create(-45, -25, 140, 1792, -80, -50, 140, 1024);
					DAT_800a5b14[1] = Tape_Create(45, -25, 140, 1792, -70, -20, 140, 1024);
					DAT_800a5b14[2] = Tape_Create(-45, 25, 140, 1792, -80, 10, 140, 1024);
					DAT_800a5b14[3] = Tape_Create(45, 25, 140, 1792, -70, 40, 140, 1024);
					break;
				case 5:
					DAT_800a5b14[0] = Tape_Create(0, 0, 140, 2304, -80, -50, 140, 1024);
					DAT_800a5b14[1] = Tape_Create(-55, -25, 140, 1536, -70, -25, 140, 1024);
					DAT_800a5b14[2] = Tape_Create(55, -25, 140, 1536, -80, 0, 140, 1024);
					DAT_800a5b14[3] = Tape_Create(-55, 25, 140, 1536, -70, 25, 140, 1024);
					DAT_800a5b14[4] = Tape_Create(55, 25, 140, 1536, -80, 50, 140, 1024);
					break;
				}
			}
			{
				int i;
				for (i = 0; i < 5; i++) {
					if (DAT_800a5b14[i]) {
						DAT_800a5b14[i]->mTapeNum = DAT_800a6844.LevelTapes[DAT_800d17c8->mSkaterIndex][0] - (NumTapes - i);
						DAT_800a5b14[i]->mSessionTapeNum = i;
					}
				}
			}
			{
				int i;
				for (i = 0; i < 5; i++) {
					if (DAT_800a5b14[i])
						DAT_800a5b14[i]->AI(DAT_800a6844.LevelTapes[DAT_800d17c8->mSkaterIndex][0] - (NumTapes - i));
				}
			}
			Mess_SetScale(256);
			Mess_SetRGB(122, 122, 122, 0);
			if (CTape::DisplayTitle()) {
				static char GotATape[25];
				if (NumTapes == 1) {
					FUN_8001e114(256, 40, DAT_800a5d5c[35], 0, 0, 256, 0);
				} else {
					FUN_8008b900(GotATape, DAT_800a5d5c[36], NumTapes);
					FUN_8001e114(256, 40, GotATape, 0, 0, 256, 0);
				}
			}
			if (CTape::DisplayContinueButton())
				Front_PrintCentredPrompt(DAT_800a5d5c[96]);
		}
		break;
	case 6:
	case 7:
	case 12:
		Mess_SetRGB(150, 100, 25, 0);
		FUN_8001e114(256, 80, DAT_800a5d5c[5], 0, 0, 256, 0);
		DAT_800d1428->mY = 130;
		DAT_800d1428->Display();
		Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		break;
	case 17:
		Mess_SetRGB(150, 100, 25, 0);
		FUN_8001e114(256, 80, DAT_800a5d5c[47], 0, 0, 256, 0);
		DAT_800d1428->mY = 130;
		DAT_800d1428->Display();
		Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		break;
	case 14:
		if (!DAT_800d13d8 && DAT_800d1514 >= 11) {
			DAT_800d142c->Display();
			Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		}
		break;
	case 15:
		if (DAT_800d1514 >= 11) {
			if (DAT_800d1780 == 2)
				DAT_800d1430->EntryOff(DAT_800a5d5c[24]);
			else
				DAT_800d1430->EntryOn(DAT_800a5d5c[24]);
			DAT_800d1430->CentreY();
			DAT_800d1430->Display();
			Front_PrintGoBackSelect();
		}
		break;
	case 16:
		if (DAT_800d1514 >= 11) {
			if (DAT_800d1780 == 2)
				DAT_800d1434->EntryOff(DAT_800a5d5c[24]);
			else
				DAT_800d1434->EntryOn(DAT_800a5d5c[24]);
			DAT_800d1434->CentreY();
			DAT_800d1434->Display();
			Front_PrintGoBackSelect();
		}
		break;
	case 34:
		{
			char horseBuf[2];
			int termFound = 0;
			int i;
			FUN_8001d250(0);
			Mess_SetRGB(122, 122, 122, 0);
			FUN_8001e114(256, 80, DAT_800a5d5c[81], 0, 0, 256, 0);
			horseBuf[1] = 0;
			for (i = 0; i < 10; i++) {
				char *pWord = DAT_800a7204;
				if (DAT_800d1100 > 0)
					DAT_800d1100--;
				if (!pWord[i])
					termFound = 1;
				horseBuf[0] = pWord[i];
				if (i == DAT_800d17b8) {
					Mess_SetRGB(182, 132, 36, 0);
					Mess_SetScale(DAT_800d1100 * 6 + 256);
				} else {
					Mess_SetRGB(122, 122, 122, 0);
					Mess_SetScale(256);
				}
				if (!termFound)
					FUN_8001e114(i * 20 + 156, 120, horseBuf, 0, 0, 256, 0);
				horseBuf[0] = '_';
				Mess_SetScale(256);
				FUN_8001e114(i * 20 + 156, 130, horseBuf, 0, 0, 256, 0);
			}
			Front_PrintCentredPrompt(DAT_800a5d5c[103]);
		}
		break;
	case 33:
		{
			char Score[10];
			Mess_SetScale(256);
			if (DAT_800d179c == 0)
				Mess_SetRGB(80, 80, 128, 0);
			else
				Mess_SetRGB(128, 80, 80, 0);
			if (DAT_800d17a0 == 0) {
				if (DAT_800d179c == 0)
					FUN_8001e114(256, 120, DAT_8009e3d4, 0, 0, 256, 0);
				else
					FUN_8001e114(256, 120, DAT_8009e3e8, 0, 0, 256, 0);
			} else {
				if (DAT_800d179c == 0)
					FUN_8001e114(256, 120, DAT_8009e3fc, 0, 0, 256, 0);
				else
					FUN_8001e114(256, 120, DAT_8009e40c, 0, 0, 256, 0);
				FUN_8008b900(Score, DAT_800d14ac, DAT_800d17a4);
				FUN_8001e114(256, 140, Score, 0, 0, 256, 0);
			}
			Horse_DisplayWords(DAT_800d17b0);
			Front_PrintCentredPrompt(DAT_800a5d5c[96]);
		}
		break;
	case 37:
		{
			static char highScoreBuf[64];
			int i;
			Mess_SetScale(256);
			FUN_8008b900(highScoreBuf, DAT_800a5d5c[80], DAT_800a5398[DAT_800d1e28].pName);
			Mess_SetRGB(182, 132, 36, 0);
			FUN_8001e114(256, 40, highScoreBuf, 0, 0, 256, 0);
			Mess_SetRGB(122, 122, 122, 0);
			for (i = 0; i < 8; i++) {
				DAT_800a5cec[i] += 30;
				if (DAT_800a5cec[i] > 180)
					DAT_800a5cec[i] = 180;
				DAT_800a5d0c[i] -= 30;
				if (DAT_800a5d0c[i] < 412)
					DAT_800a5d0c[i] = 412;
				if (i == DAT_800d13dc)
					Mess_SetRGB(182, 132, 36, 0);
				else
					Mess_SetRGB(122, 122, 122, 0);
				if (DAT_800d1100 > 0)
					DAT_800d1100--;
				highScoreBuf[1] = 0;
				highScoreBuf[0] = DAT_800a6844.HighScores[DAT_800d1e28][i].Name[0];
				FUN_8001d250(0);
				if (i == DAT_800d13dc && DAT_800d13e0 == 0)
					Mess_SetScale(DAT_800d1100 * 6 + 256);
				else
					Mess_SetScale(256);
				FUN_8001e114(DAT_800a5cec[i] - 80, (i + 1) * 19 + 40, highScoreBuf, 0, 0, 256, 0);
				Mess_SetScale(256);
				highScoreBuf[0] = DAT_800a6844.HighScores[DAT_800d1e28][i].Name[1];
				FUN_8001d250(0);
				if (i == DAT_800d13dc && DAT_800d13e0 == 1)
					Mess_SetScale(DAT_800d1100 * 6 + 256);
				else
					Mess_SetScale(256);
				FUN_8001e114(DAT_800a5cec[i] - 60, (i + 1) * 19 + 40, highScoreBuf, 0, 0, 256, 0);
				Mess_SetScale(256);
				highScoreBuf[0] = DAT_800a6844.HighScores[DAT_800d1e28][i].Name[2];
				FUN_8001d250(0);
				if (i == DAT_800d13dc && DAT_800d13e0 == 2)
					Mess_SetScale(DAT_800d1100 * 6 + 256);
				else
					Mess_SetScale(256);
				FUN_8001e114(DAT_800a5cec[i] - 40, (i + 1) * 19 + 40, highScoreBuf, 0, 0, 256, 0);
				Mess_SetScale(256);
				if (i == DAT_800d13dc && (DAT_800d16e4 / 10) & 1) {
					int x;
					FUN_8008b900(highScoreBuf, DAT_800d14b0);
					FUN_8001d250(0);
					x = DAT_800d13e0 * 20 - 80;
					FUN_8001e114(DAT_800a5cec[i] + x, (i + 1) * 19 + 48, highScoreBuf, 0, 0, 256, 0);
				}
				FUN_8008b900(highScoreBuf, DAT_800d14b4, DAT_800a4528[DAT_800a6844.HighScores[DAT_800d1e28][i].Skater].pName);
				{
					char *p = highScoreBuf;
					while (*p) {
						if (*p == ' ') {
							*p = 0;
							break;
						}
						p++;
					}
				}
				FUN_8001d250(1);
				FUN_8001e114(DAT_800a5cec[i], (i + 1) * 19 + 40, highScoreBuf, 0, 0, 256, 0);
				FUN_8008b900(highScoreBuf, DAT_800d14ac, DAT_800a6844.HighScores[DAT_800d1e28][i].Score);
				FUN_8001d250(2);
				FUN_8001e114(DAT_800a5d0c[i], (i + 1) * 19 + 40, highScoreBuf, 0, 0, 256, 0);
			}
			Front_PrintCentredPrompt(DAT_800a5d5c[103]);
		}
		break;
	case 13:
		Mess_SetScale(256);
		if (DAT_800d1780 == 1) {
			Mess_SetRGB(182, 132, 36, 0);
			FUN_8001e114(256, 40, DAT_800a5d5c[37], 0, 0, 256, 0);
		} else {
			Mess_SetRGB(182, 132, 36, 0);
			if (DAT_800d16a4 == 7)
				FUN_8001e114(256, 40, DAT_8009e41c, 0, 0, 256, 0);
			else
				FUN_8001e114(256, 40, DAT_8009e428, 0, 0, 256, 0);
		}
		Mess_SetRGB(122, 122, 122, 0);
		Mess_SetScale(256);
		if (DAT_800d1780 == 1) {
			int i;
			FUN_8001d250(1);
			for (i = 0; i < 5; i++) {
				DAT_800a5cec[i] += 30;
				if (DAT_800a5cec[i] > 90)
					DAT_800a5cec[i] = 90;
			}
			Line = 0;
			FUN_8001e114(DAT_800a5cec[0], Line++ * 18 + 60, DAT_800a5d5c[38], 0, 0, 256, 0);
			FUN_8001e114(DAT_800a5cec[1], Line++ * 18 + 60, DAT_800a5d5c[39], 0, 0, 256, 0);
			if (DAT_800d16a4 == 1) {
				FUN_8001e114(DAT_800a5cec[2], Line++ * 18 + 60, DAT_800a5d5c[40], 0, 0, 256, 0);
			}
			FUN_8001e114(DAT_800a5cec[3], Line++ * 18 + 60, DAT_800a5d5c[41], 0, 0, 256, 0);
			FUN_8001e114(DAT_800a5cec[4], Line * 18 + 60, DAT_800a5d5c[42], 0, 0, 256, 0);
			FUN_8001d250(0);
			pMan = DAT_800d19a4;
			FUN_8001d250(2);
			for (i = 0; i < 5; i++) {
				DAT_800a5d0c[i] -= 30;
				if (DAT_800a5d0c[i] < 410)
					DAT_800a5d0c[i] = 410;
			}
			Line = 0;
			FUN_8008b900(Score1, DAT_800d14ac, pMan->mScore);
			FUN_8001e114(DAT_800a5d0c[0], Line++ * 18 + 60, Score1, 0, 0, 256, 0);
			FUN_8008b900(Score2, DAT_800d14ac, DAT_800a6844.HighScores[DAT_800d1e28][0].Score);
			FUN_8001e114(DAT_800a5d0c[1], Line++ * 18 + 60, Score2, 0, 0, 256, 0);
			if (DAT_800d16a4 == 1) {
				FUN_8008b900(Tapes, DAT_8009e434, Career_LevelTapes(DAT_800d1e28), 5);
				FUN_8001e114(DAT_800a5d0c[2], Line++ * 18 + 60, Tapes, 0, 0, 256, 0);
			}
			FUN_8008b900(Tricks, DAT_800d14b8, pMan->mTricksLanded);
			FUN_8001e114(DAT_800a5d0c[3], Line++ * 18 + 60, Tricks, 0, 0, 256, 0);
			FUN_8008b900(Bails, DAT_800d14b8, pMan->mBails);
			FUN_8001e114(DAT_800a5d0c[4], Line * 18 + 60, Bails, 0, 0, 256, 0);
			if (DAT_800a5cec[0] == 90) {
				FUN_8001d250(0);
				if (!pMan->mBestComboScore) {
					Mess_SetScale(220);
					FUN_8001e114(256, 151, DAT_800a5d5c[43], 0, 0, 256, 0);
					Mess_SetScale(256);
					FUN_8001e114(256, 168, DAT_800a5d5c[44], 0, 0, 256, 0);
				} else {
					if (pMan->mBestComboTricks == 1)
						FUN_8008b900(BestCombo, DAT_800a5d5c[46], pMan->mBestComboTricks, pMan->mBestComboScore);
					else
						FUN_8008b900(BestCombo, DAT_800a5d5c[45], pMan->mBestComboTricks, pMan->mBestComboScore);
					Mess_SetScale(220);
					FUN_8001e114(256, 151, BestCombo, 0, 0, 256, 0);
					Mess_SetScale(188);
					FUN_8001e114(256, 166, pMan->mBestCombo1, 0, 0, 256, 0);
					FUN_8001e114(256, 180, pMan->mBestCombo2, 0, 0, 256, 0);
					FUN_8001e114(256, 194, pMan->mBestCombo3, 0, 0, 256, 0);
				}
			}
		} else {
			int s1, s2;
			Mess_SetScale(256);
			s1 = DAT_800d17c8->mScore;
			s2 = 0;
			if (DAT_800d17cc)
				s2 = DAT_800d17cc->mScore;
			switch (DAT_800d16a4) {
			case 8:
				if (DAT_800d17cc->mGraffitiCount == DAT_800d17c8->mGraffitiCount)
					FUN_8001e114(256, 64, DAT_800d14bc, 0, 0, 256, 0);
				else if (DAT_800d17c8->mGraffitiCount < DAT_800d17cc->mGraffitiCount)
					FUN_8001e114(256, 64, DAT_8009e440, 0, 0, 256, 0);
				else
					FUN_8001e114(256, 64, DAT_8009e450, 0, 0, 256, 0);
				Mess_SetScale(224);
				Graffiti_Stats(DAT_800d17c8, 30, 86, 32, 32, 128, DAT_800d1954, DAT_800d1958, DAT_800d195c, DAT_800d1960);
				Graffiti_Stats(DAT_800d17cc, 286, 86, 128, 32, 32, DAT_800d1964, DAT_800d1968, DAT_800d196c, DAT_800d1970);
				break;
			case 7:
				{
					char Score[40];
					DAT_800d14fc = DAT_800d17a0;
					DAT_800d1500 = DAT_800d179c;
					DAT_800d1504 = DAT_800d17a4;
					DAT_800d1508 = DAT_800d17ac;
					DAT_800d150c[0] = DAT_800d17b0[0];
					DAT_800d150c[1] = DAT_800d17b0[1];
					Line = 0;
					if (DAT_800d179c == 0)
						Mess_SetRGB(80, 80, 128, 0);
					else
						Mess_SetRGB(128, 80, 80, 0);
					if (DAT_800d17a0 == 0) {
						DAT_800d17a4 = DAT_800d17c8->mHorseScore;
						if (DAT_800d17a4) {
							FUN_8008b900(Score, DAT_8009e460, DAT_800d17a4);
							FUN_8001e114(256, 80, Score, 0, 0, 256, 0);
							DAT_800d14fc ^= 1;
							DAT_800d1500 ^= 1;
						} else {
							FUN_8001e114(256, 80, DAT_8009e470, 0, 0, 256, 0);
							DAT_800d1500 ^= 1;
						}
					} else {
						FUN_8008b900(Score, DAT_8009e484, DAT_800d17a4);
						FUN_8001e114(256, Line++ * 24 + 80, Score, 0, 0, 256, 0);
						FUN_8008b900(Score, DAT_8009e494, DAT_800d17c8->mHorseScore);
						FUN_8001e114(256, Line++ * 24 + 80, Score, 0, 0, 256, 0);
						if (DAT_800d17c8->mHorseScore == (uint)DAT_800d17a4) {
							FUN_8001e114(256, Line * 24 + 80, DAT_800d14c0, 0, 0, 256, 0);
							DAT_800d1500 ^= 1;
						} else if (DAT_800d17c8->mHorseScore < (uint)DAT_800d17a4) {
							char YouAre[40];
							int Letters = DAT_800d150c[DAT_800d179c]++;
							if (Letters + 1 == DAT_800a6844.HorseLength) {
								char c = DAT_800a6844.HorseWord[0];
								if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
									FUN_8008b900(YouAre, DAT_8009e4a4);
								else
									FUN_8008b900(YouAre, DAT_8009e4b0);
								if (!DAT_800d13c4) {
									DAT_800d14f8 += 32;
									if (DAT_800d14f8 > 512) {
										Mess_SetRGB(255, 48, 48, 0);
										DAT_800d14f8 = 512;
									}
									Mess_SetScale(DAT_800d14f8);
									FUN_8001e114(256, 152, YouAre, 0, 0, 256, 0);
									Mess_SetScale(DAT_800d14f8 <= 512 ? DAT_800d14f8 : 512);
									FUN_8001e114(256, 188, DAT_800a7204, 0, 0, 256, 0);
									DAT_800d17bc = 45;
									Front_PrintCentredPrompt(DAT_800a5d5c[96]);
								} else {
									if (!DAT_800d14f4) {
										SFX_PlayX(42, 8192, 0);
										DAT_800d14f4 = 1;
									}
									FUN_8001e07c(DAT_800a5b28);
									FUN_8001e0f8(DAT_800a5b28, 512);
									FUN_8001e0a4(DAT_800a5b28, 1);
									FUN_8001e114(256, 152, YouAre, 0, 0, 256, 0);
									if (FUN_8001e108(DAT_800a5b28))
										DAT_800d17bc = 45;
									FUN_8001e0a4(DAT_800a5b28, 0);
									FUN_8001e0a4(DAT_800a5b28, 1);
									FUN_8001e114(256, 188, DAT_800a7204, 0, 0, 256, 0);
									FUN_8001e0a4(DAT_800a5b28, 0);
								}
								DAT_800d14fc = 2;
							} else {
								YouAre[1] = 0;
								YouAre[0] = DAT_800a6844.HorseWord[Letters];
								if (DAT_800d14f8 < 512) {
									DAT_800d14f8 += 32;
									if (DAT_800d14f8 > 512)
										DAT_800d14f8 = 512;
									Mess_SetScale(DAT_800d14f8 <= 384 ? DAT_800d14f8 : 384);
									FUN_8001e114(256, 152, DAT_800a5d5c[88], 0, 0, 256, 0);
									Mess_SetScale(DAT_800d14f8 <= 512 ? DAT_800d14f8 : 512);
									FUN_8001e114(256, 188, YouAre, 0, 0, 256, 0);
									DAT_800d17bc = 45;
								} else {
									if (!DAT_800d14f4) {
										SFX_PlayX(42, 8192, 0);
										DAT_800d14f4 = 1;
									}
									FUN_8001e07c(DAT_800a5b28);
									FUN_8001e0f8(DAT_800a5b28, 384);
									FUN_8001e0a4(DAT_800a5b28, 1);
									FUN_8001e114(256, 152, DAT_800a5d5c[88], 0, 0, 256, 0);
									if (FUN_8001e108(DAT_800a5b28))
										DAT_800d17bc = 45;
									FUN_8001e0a4(DAT_800a5b28, 0);
									FUN_8001e0f8(DAT_800a5b28, 512);
									FUN_8001e0a4(DAT_800a5b28, 1);
									FUN_8001e114(256, 188, YouAre, 0, 0, 256, 0);
									FUN_8001e0a4(DAT_800a5b28, 0);
								}
								if (++DAT_800d1508 == DAT_800d19dc)
									DAT_800d1508 = 0;
								DAT_800d1500 ^= 1;
								DAT_800d14fc ^= 1;
							}
						} else {
							FUN_8001e114(256, Line * 24 + 80, DAT_800d14c8, 0, 0, 256, 0);
							DAT_800d1500 ^= 1;
							DAT_800d1504 = DAT_800d17c8->mHorseScore;
						}
					}
					Horse_DisplayWords(DAT_800d150c);
				}
				break;
			case 6:
			default:
				FUN_8008b900(Score1, DAT_8009e4bc, s1);
				FUN_8008b900(Score2, DAT_8009e4cc, s2);
				FUN_8001e114(256, 75, Score1, 0, 0, 256, 0);
				FUN_8001e114(256, 99, Score2, 0, 0, 256, 0);
				if (s2 < s1)
					FUN_8001e114(256, 123, DAT_8009e450, 0, 0, 256, 0);
				else if (s1 < s2)
					FUN_8001e114(256, 123, DAT_8009e440, 0, 0, 256, 0);
				else
					FUN_8001e114(256, 123, DAT_800d14d0, 0, 0, 256, 0);
				break;
			}
		}
		if (DAT_800d16a4 != 7 && DAT_800d1514 >= 11)
			Front_PrintCentredPrompt(DAT_800a5d5c[96]);
		break;
	case 5:
		Mess_SetRGB(150, 100, 25, 0);
		FUN_8001e114(256, 103, DAT_800a5d5c[97], 0, 0, 256, 0);
		DAT_800d1428->mY = 143;
		DAT_800d1428->Display();
		Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		break;
	case 24:
		if (DAT_800d1514 >= 11) {
			DAT_800d143c->Display();
			Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		}
		break;
	case 25:
		if (DAT_800d1514 >= 11) {
			if (DAT_800d1780 == 2)
				DAT_800d1438->EntryOff(DAT_800a5d5c[24]);
			else
				DAT_800d1438->EntryOn(DAT_800a5d5c[24]);
			DAT_800d1438->CentreY();
			DAT_800d1438->Display();
			Front_PrintGoBackSelect();
		}
		break;
	case 27:
		Competition_EndGameDisplay();
		break;
	case 23:
		Competition_WinLoseDisplay();
		break;
	case 22:
		Competition_LadderDisplay();
		break;
	case 20:
		Competition_JudgeDisplay();
		break;
	case 38:
		DAT_800d1440->Display();
		Front_PrintCentredPrompt(DAT_800a5d5c[102]);
		break;
	}
}
