/* FUN_80059794 (0x80059794) size=9180 flags=-fstructure-noalias,-fstrict-aliasing */
/* C++ (front end, 1-player skater select; called from the screen dispatcher FUN_8005bb70). The
   selected skater (DAT_800d1c40) spins as a 3D CBruce in the right-hand window and slides out/in
   when left/right is pressed (or a "LOADING" label slides while the model streams in). The name
   slides in under a bar, four stat rows draw bar sprites (skater stats plus the best unlocked
   board's), the six bio lines are printed, and the career's tapes and the three competition medals
   (Skate Park, Burnside, Roswell) are shown in an item box. The secret 11th skater unlocks once any
   skater has 30 tapes. X/Start picks the skater (returns its index), triangle backs out (-1).
   size=9180 covers the whole TU tail: this function, FUN_8005bad0, and the out-of-line copy of
   CItem's inline virtual destructor (FUN_8005bb3c). No #pragma interface, so _vt.5CItem lands in
   .rdata before the jump tables, as in retail. Levers: the main loop is a for(;;) whose exits are
   all `goto done` (a `break` lets expand_end_loop roll the leading exit test to the bottom), and
   FUN_80093240 (RotMatrix) returns MATRIX*. */
typedef unsigned char uchar;
typedef unsigned int uint;

struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle, Square, Circle, X;
	SButton LeftOne, LeftTwo, RightOne, RightTwo;
	SButton Left, Right, Up, Down;
	SButton AnalogueLeft, AnalogueRight, Start, Select;
	SButton Crouch, Jump, SmartBomb, SelectWeapon;
	int rest[11];
};
struct SBoard {
	char *Name;                /* 0 */
	uchar Req;                 /* 4: tapes needed */
	int Stats[4];              /* 8 */
	int pad[2];
};
struct SSkater {
	char pad0[8];
	char *pModel;              /* 0x08 */
	char pad0c[0x13 - 0x0c];
	uchar m13;                 /* 0x13 */
	signed char m14;           /* 0x14 */
	char pad15[0x18 - 0x15];
	int Stats[4];              /* 0x18 */
	char pad28[0x2c - 0x28];
	char *pName;               /* 0x2c */
	char *pBio[6];             /* 0x30 */
	char pad48[0x58 - 0x48];
	SBoard Boards[7];          /* 0x58 */
	char pad138[340 - 0x138];
};
struct SSkaterCareer {
	uchar NumTapes;            /* 0 (0x8 + 14 * n in SCareer) */
	uchar pad1[3];
	uchar Medals[6];           /* 4: per competition */
	uchar pada[4];
};
struct SCareer {
	int Version;
	int m4;
	SSkaterCareer Skater[148];
	char pad[0x824 - 8 - 148 * 14];
	char LastSkater[2];        /* 0x824 */
	char LastDeck[2];          /* 0x826 */
	char LastWheel[2];         /* 0x828 */
	char LastTrucks[2];        /* 0x82a */
	char m82c;                 /* 0x82c */
};
struct SCompetition {
	char *Name;
	char pad[120 - 4];
};
struct SVECTOR { short vx, vy, vz, pad; };
struct MATRIX { short m[3][3]; int t[3]; };
struct SStatRow {
	int x, y, value;
	int pad[2];
	int bar;
};

class CItem {
public:
	virtual ~CItem() {}
	void *operator new(uint) throw();
};
class SlicedImage;
class Sprite : public CItem {
public:
	int m_w;
	int m_h;
	int m_packed;
	int m_bpp;
	SlicedImage *m_image;
	Sprite(char *, int, int, int);
	Sprite(int, int, int, int, int, int, int);
	~Sprite();
	void draw(int, int, int, int, int, int);
	void pack();
	void unpack();
	void removeFromMemory();
};
class MenuInput : public CItem {
public:
	int pad[(0x11c - 4) / 4];
	MenuInput(int);
	void update();
	int getPress();
};
class SaveRect : public CItem {
public:
	short x, y, w, h;
	void *buf;
	SaveRect(int, int, int, int);
	~SaveRect();
	void restore(int, int);
};
class PREManager {
public:
	void unloadPRE(char *);
};
class CSuper {
public:
	int m0;
	int mX;                    /* 0x04 */
	char pad8[0x48 - 8];
	virtual ~CSuper();
};
class CBruce : public CSuper {
public:
	char pad4c[0x78c - 0x4c];
	MATRIX mRotMatrix;         /* 0x78c */
};

extern SControl DAT_800c0a48[];
extern SCareer DAT_800a6844;
extern SSkater DAT_800a44fc[];
extern SCompetition DAT_800a5398[];
extern int DAT_800d37b4[];
extern int DAT_800d37e4[];
extern int DAT_800d1cb8;
extern int DAT_800d16a4;
extern int DAT_800d1724;
extern int DAT_800d1afc;
extern int DAT_800d2120;
extern int DAT_800d2130;
extern char *DAT_800d19a4;
extern char *DAT_800d1a48;
extern char DAT_800c119c[];
extern PREManager *DAT_800d1b10;
static int DAT_800d232c;
static int DAT_800d2330;
static int DAT_800d2334;
static int DAT_800d2340;
static int DAT_800d2344;
static int DAT_800d2328;

int DAT_800d1c40 = 0;          /* selected skater */
int DAT_800d1c44 = 0;
int DAT_800d1c48 = 0x11b1;
int DAT_800d1c4c = 0x11b1;
int DAT_800d1c50 = 30;
int DAT_800d1c54 = 70;
int DAT_800d1c58 = 16;         /* slide speed */
int DAT_800d1c5c = -1;
int DAT_800d1c60 = 0;          /* secret skater unlocked */
int DAT_800d1c64 = 0;          /* ... as of the last visit */

typedef char SLabel6[6] __attribute__((aligned(4)));

void Pad_ClearTriggers(SControl *);
void Pack_DefragmentFully();
void Mess_SetRGB(uchar, uchar, uchar, int);
void Mess_SetFontScale(uint);
void Mess_SetCurrentFont(char *);
int Mess_TextHeight(const char *);
void Mess_LoadFont(char *, int, int, int);
void Mess_UnloadFont();
void M3d_BuildTransform(CSuper *);
extern "C" {
void FUN_8005c97c(int);
void *FUN_8005ca3c(char *);
void FUN_8004d5d0(void *);
void FUN_8005ca64(void);
void FUN_80061714(void *);
void FUN_80059520(int);
int FUN_8008b900(char *, const char *, ...);
void FUN_8008c468(int);
void FUN_80059050(void);
short *FUN_8006b1c8(void);
int FUN_8001db80(const char *);
int FUN_8001da44(char *);
int FUN_8001dc9c(char *);
void FUN_8001d250(int);
void FUN_8001e114(int, int, char *, int, int, int, int);
uchar *FUN_8004d068(int, int, int);
void FUN_8005c8dc(int);
void FUN_80059618(int);
void FUN_8005c780(void);
void FUN_80070ff4(void);
void FUN_8005c68c(void);
void FUN_800242cc(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_80059094(void);
void FUN_8005c934(void);
void FUN_8004b250(int, int, int);
void FUN_8006ed2c(int);
void FUN_8006f290(int);
CBruce *FUN_8005933c(void);
void FUN_8006fde4(int, int, int);
void FUN_8006edb8(int);
void FUN_800596a0(void);
MATRIX *FUN_80093240(SVECTOR *, MATRIX *);
void FUN_80043f70(CBruce *);
void FUN_800831f8(char *, short *, char *);
void FUN_80083838(char *);
void FUN_80083774(void);
void FUN_80059018(void);
int FUN_8008f6fc(char *, char *);
void FUN_80061e00(int, int, int, int);
void FUN_8005948c(void);
void FUN_8006b2f4(void);
void FUN_8006af64(void);
void FUN_8004cdd0(void);
void FUN_800591c0(void);
void FUN_80059758(void);
}

extern "C" int FUN_80059794()
{
	char text[40];             /* unused */
	char name[16];
	Sprite *bar[5];
	SStatRow rows[4];
	int bonus[4];
	Sprite *medal[3];
	int medalType[3];
	int i;

	int result = 0;
	int numSkaters = 10;
	DAT_800d1c60 = 0;
	DAT_800d1c40 = DAT_800a6844.LastSkater[0];
	for (i = 0; i < 11; i++) {
		if (DAT_800a6844.Skater[i].NumTapes >= 30) {
			DAT_800d1c60 = 1;
			numSkaters = 11;
		}
	}
	if (!DAT_800d1c64 && DAT_800d1c60)
		DAT_800d1c40 = 10;
	else if (DAT_800d1c40 == 10 && !DAT_800d1c60)
		DAT_800d1c40 = 0;
	DAT_800d1c64 = DAT_800d1c60;

	Pad_ClearTriggers(&DAT_800c0a48[0]);
	Pad_ClearTriggers(&DAT_800c0a48[1]);
	FUN_8005c97c(1);
	FUN_8004d5d0(FUN_8005ca3c("select2p.bmp"));
	FUN_8005ca64();
	FUN_80061714(FUN_8005ca3c("selectp.bmp"));
	Pack_DefragmentFully();
	Mess_LoadFont("stats1.fnt", -1, -1, -1);
	FUN_80059520(1);

	for (i = 0; i < 5; i++) {
		if (i < 4)
			FUN_8008b900(name, "bar%d.bmp", i + 1);
		else
			FUN_8008b900(name, "bar9.bmp", i + 1);
		bar[i] = new Sprite(name, 1, 32, 128);
		bar[i]->removeFromMemory();
	}
	for (int r = 0; r < 4; r++) {
		rows[r].x = 203;
		rows[r].y = r * 24 + 195;
		rows[r].bar = r;
	}
	rows[0].value = DAT_800a44fc[DAT_800d1c40].Stats[0];
	rows[1].value = DAT_800a44fc[DAT_800d1c40].Stats[1];
	rows[2].value = DAT_800a44fc[DAT_800d1c40].Stats[2];
	rows[3].value = DAT_800a44fc[DAT_800d1c40].Stats[3];

	SaveRect *bioRect1 = new SaveRect(203, 287, 188, 33);
	SaveRect *bioRect2 = new SaveRect(203, 320, 188, 94);
	Sprite *statBox = new Sprite(203, 180, 200, 95, 1, 32, 128);
	statBox->removeFromMemory();

	char *comps[3] = { "Skate Park", "Burnside", "Roswell" };
	for (i = 0; i < 3; i++) {
		FUN_8008b900(name, "medal%d.bmp", i + 1);
		medal[i] = new Sprite(name, 1, 32, 128);
		medal[i]->removeFromMemory();
		medalType[i] = -1;
	}
	Sprite *arrow[4];
	for (i = 0; i < 4; i++) {
		FUN_8008b900(name, "levbut%d.bmp", i + 1);
		arrow[i] = new Sprite(name, 1, 32, 128);
		arrow[i]->removeFromMemory();
	}
	uint leftTimer = 0;
	uint rightTimer = 0;
	Sprite *nameBar = new Sprite(0, 54, 478, 33, 1, 32, 128);
	nameBar->removeFromMemory();
	Sprite *topBox = new Sprite(400, 92, 183, 111, 1, 32, 128);
	Sprite *bottomBox = new Sprite(400, 203, 183, 111, 1, 32, 128);
	topBox->removeFromMemory();
	bottomBox->removeFromMemory();
	FUN_8008c468(0);
	FUN_80059050();
	FUN_8008c468(0);

	SVECTOR rot;
	rot.vx = rot.vy = rot.vz = 0;
	short *viewport = FUN_8006b1c8();
	CBruce *pBruce = 0;
	int state = 0;
	int speed = DAT_800d1c58;
	int settle = 0;
	int dir;
	int wait;
	int loadX = 491;
	int noTapes = 1;
	viewport[0] = 640;
	viewport[1] = 480;
	for (int k = 0; k < 11; k++) {
		if (DAT_800a6844.Skater[k].NumTapes) {
			noTapes = 0;
			break;
		}
	}
	int blink = 96;
	int nameX;
	int nameY;
	int nameL;
	int nameR;
	int nameStep;
	int nameState = 0;
	Sprite *itemBox = 0;
	Sprite *itemBoxBack = 0;
	SLabel6 sStart = "start";
	int hintX[2];              /* unused */
	char first[16];
	int hintY[2];
	hintY[0] = 193;
	hintY[1] = 213;
	if (DAT_800d16a4 == 1) {
		itemBox = new Sprite("itembox1.bmp", 1, 32, 128);
		itemBoxBack = new Sprite(395, 313, 240, 102, 0, 32, 128);
	}
	Mess_LoadFont("tapes1.fnt", -1, -1, -1);
	Mess_SetFontScale(255);
	char tapes[3];
	tapes[0] = '0';
	tapes[1] = '0';
	tapes[2] = 0;
	int tapesY = (Mess_TextHeight(tapes) >> 1) + 385 - FUN_8001db80(tapes);
	MenuInput input(-1);
	int textTimer = 0;
	int statTimer = 0;
	int medalTimer = 0;
	uchar *flags = FUN_8004d068(10, 1, 1);
	FUN_8005c8dc(9);
	FUN_80059618(0);

	for (;;) {
		FUN_8005c780();
		FUN_80070ff4();
		FUN_8005c68c();
		if (DAT_800d1cb8)
			goto done;
		FUN_800242cc();
		FUN_8006b240();
		FUN_80061ea0();
		input.update();
		if (!DAT_800d2340)
			FUN_80059094();
		else
			FUN_8005c934();

		int done = 0;
		switch (state) {
		case 0:
		default:
			rot.vy += 10;
			{
				int press = input.getPress();
				if (press == 2) {
					FUN_8004b250(148, 0x2000, 0);
					state = 1;
					nameState = 4;
					rightTimer = 20;
					dir = 0;
					blink = 96;
				} else if (press == 1) {
					FUN_8004b250(148, 0x2000, 0);
					state = 2;
					nameState = 4;
					leftTimer = 20;
					dir = 1;
					blink = 96;
				}
			}
			if (!DAT_800d2344 && DAT_800d37e4[DAT_800d1c40]) {
				DAT_800d2344 = 1;
				if (*DAT_800a44fc[DAT_800d1c40].pModel) {
					FUN_8006ed2c(DAT_800d37b4[DAT_800d1c40]);
					if (DAT_800d1724) {
						DAT_800d2120 = DAT_800a44fc[DAT_800d1c40].m13;
						DAT_800d2130 = DAT_800a44fc[DAT_800d1c40].m14;
					}
					FUN_8006f290(DAT_800d37b4[DAT_800d1c40]);
					DAT_800d2120 = -1;
				}
				pBruce = FUN_8005933c();
				pBruce->mX = DAT_800d232c;
			}
			break;
		case 1:
			if (DAT_800d2344) {
				pBruce->mX -= speed << 12;
				if (!settle && pBruce->mX < DAT_800d2334)
					settle = 2;
				else if (settle > 0 && --settle == 0)
					state = 5;
			} else {
				loadX -= speed;
				if (loadX < 400)
					state = 5;
			}
			break;
		case 2:
			if (DAT_800d2344) {
				pBruce->mX += speed << 12;
				if (!settle && pBruce->mX >= DAT_800d2330)
					settle = 2;
				else if (settle > 0 && --settle == 0)
					state = 5;
			} else {
				loadX += speed;
				if (loadX >= 583)
					state = 5;
			}
			break;
		case 3:
			if (DAT_800d2344) {
				pBruce->mX += speed << 12;
				if (pBruce->mX >= DAT_800d232c)
					done = 1;
			} else {
				loadX += speed;
				if (loadX >= 491)
					done = 1;
			}
			if (done) {
				state = 0;
				pBruce->mX = DAT_800d232c;
				int press = input.getPress();
				if (press == 2) {
					FUN_8004b250(148, 0x2000, 0);
					state = 1;
					nameState = 4;
					rightTimer = 20;
					dir = 0;
				} else if (press == 1) {
					FUN_8004b250(148, 0x2000, 0);
					state = 2;
					nameState = 4;
					leftTimer = 20;
					dir = 1;
				}
			}
			break;
		case 4:
			if (DAT_800d2344) {
				pBruce->mX -= speed << 12;
				if (pBruce->mX < DAT_800d232c)
					done = 1;
			} else {
				loadX -= speed;
				if (loadX < 491)
					done = 1;
			}
			if (done) {
				state = 0;
				pBruce->mX = DAT_800d232c;
				int press = input.getPress();
				if (press == 2) {
					FUN_8004b250(148, 0x2000, 0);
					state = 1;
					nameState = 4;
					rightTimer = 20;
					dir = 0;
				} else if (press == 1) {
					FUN_8004b250(148, 0x2000, 0);
					state = 2;
					nameState = 4;
					leftTimer = 20;
					dir = 1;
				}
			}
			break;
		case 5:
			state = 6;
			wait = 2;
			if (DAT_800d2344) {
				delete pBruce;
				if (*DAT_800a44fc[DAT_800d1c40].pModel) {
					FUN_8006fde4(DAT_800d37b4[DAT_800d1c40], 1, 1);
					FUN_8006edb8(DAT_800d37b4[DAT_800d1c40]);
				}
			}
			if (dir == 0 && ++DAT_800d1c40 >= numSkaters)
				DAT_800d1c40 = 0;
			else if (dir == 1 && --DAT_800d1c40 < 0)
				DAT_800d1c40 = numSkaters - 1;
			DAT_800d2344 = 0;
			FUN_800596a0();
			if (itemBoxBack)
				itemBoxBack->pack();
			break;
		case 6:
			if (--wait == 0) {
				state = 7;
				if (itemBoxBack)
					itemBoxBack->unpack();
				FUN_800596a0();
			}
			break;
		case 7:
			DAT_800d2344 = DAT_800d37e4[DAT_800d1c40];
			if (DAT_800d2344) {
				if (*DAT_800a44fc[DAT_800d1c40].pModel) {
					FUN_8006ed2c(DAT_800d37b4[DAT_800d1c40]);
					if (DAT_800d1724) {
						DAT_800d2130 = DAT_800a44fc[DAT_800d1c40].m14;
						DAT_800d2120 = DAT_800a44fc[DAT_800d1c40].m13;
					}
					FUN_8006f290(DAT_800d37b4[DAT_800d1c40]);
					DAT_800d2120 = -1;
				}
				pBruce = FUN_8005933c();
				if (dir == 1)
					pBruce->mX = DAT_800d2334;
				else
					pBruce->mX = DAT_800d2330;
			}
			nameState = 0;
			rows[0].value = DAT_800a44fc[DAT_800d1c40].Stats[0];
			rows[1].value = DAT_800a44fc[DAT_800d1c40].Stats[1];
			rows[2].value = DAT_800a44fc[DAT_800d1c40].Stats[2];
			rows[3].value = DAT_800a44fc[DAT_800d1c40].Stats[3];
			if (dir == 1) {
				state = 3;
				loadX = 400;
			} else {
				state = 4;
				loadX = 583;
			}
			break;
		}

		topBox->draw(400, 92, 0, -1, -1, -1);
		bottomBox->draw(400, 203, 0, -1, -1, -1);
		if (DAT_800d2344) {
			FUN_80093240(&rot, &pBruce->mRotMatrix);
			pBruce->mRotMatrix.m[0][1] = -pBruce->mRotMatrix.m[0][1];
			pBruce->mRotMatrix.m[1][1] = -pBruce->mRotMatrix.m[1][1];
			pBruce->mRotMatrix.m[2][1] = -pBruce->mRotMatrix.m[2][1];
			if (pBruce->mX >= DAT_800d2334 && pBruce->mX <= DAT_800d2330) {
				M3d_BuildTransform(pBruce);
				FUN_80043f70(pBruce);
				FUN_800831f8(DAT_800c119c, viewport, DAT_800d1a48 + 140);
				FUN_80083838(DAT_800d19a4);
				FUN_80083774();
			}
			if (--blink == 0)
				blink = 96;
			if (!noTapes && !state && !DAT_800a6844.Skater[DAT_800d1c40].NumTapes && blink >= 23 && DAT_800d16a4 == 1) {
				Mess_SetCurrentFont("stats1.fnt");
				Mess_SetRGB(250, 190, 60, 0);
				FUN_8001d250(0);
				int n;
				for (n = 0; n < 15; n++) {
					if (DAT_800a44fc[DAT_800d1c40].pName[n] == ' ')
						break;
					first[n] = DAT_800a44fc[DAT_800d1c40].pName[n];
				}
				first[n] = 0;
				FUN_8001e114(491, hintY[0], sStart, 1, 0, 256, 0);
				FUN_8001e114(491, hintY[1], first, 1, 0, 256, 0);
			}
		} else if (!state) {
			Mess_SetCurrentFont("stats1.fnt");
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(0);
			FUN_8001e114(loadX, 203, "LOADING", 0, 0, 256, 0);
		}

		if (leftTimer) {
			if (--leftTimer < 4)
				arrow[0]->draw(357, 95, 0, -1, -1, -1);
			else
				arrow[2]->draw(357, 95, 0, -1, -1, -1);
		}
		if (rightTimer) {
			if (--rightTimer < 4)
				arrow[1]->draw(585, 95, 0, -1, -1, -1);
			else
				arrow[3]->draw(585, 95, 0, -1, -1, -1);
		}

		if (medalTimer && DAT_800d16a4 == 1 && DAT_800a6844.Skater[DAT_800d1c40].NumTapes) {
			itemBox->draw(395, 313, 0, -1, -1, -1);
			Mess_SetCurrentFont("tapes1.fnt");
			FUN_8001d250(1);
			FUN_8001e114(476, tapesY, tapes, 0, 0, 256, 0);
			int my = 333;
			for (int m = 0; m < 3; m++) {
				if (medalType[m] != -1)
					medal[medalType[m]]->draw(583, my, 0, -1, -1, -1);
				my += 24;
			}
		} else if (DAT_800d16a4 == 1 && state == 6) {
			itemBoxBack->draw(395, 313, 0, -1, -1, -1);
		}
		FUN_80059018();

		if (statTimer) {
			statTimer--;
			if (statTimer == 2 || statTimer == 3)
				statBox->draw(203, 180, 0, -1, -1, -1);
			int best = 0;
			while (best < 7) {
				if (DAT_800a6844.Skater[DAT_800d1c40].NumTapes < DAT_800a44fc[DAT_800d1c40].Boards[best + 1].Req)
					break;
				best++;
			}
			bonus[0] = DAT_800a44fc[DAT_800d1c40].Boards[best].Stats[0];
			bonus[1] = DAT_800a44fc[DAT_800d1c40].Boards[best].Stats[1];
			bonus[2] = DAT_800a44fc[DAT_800d1c40].Boards[best].Stats[2];
			bonus[3] = DAT_800a44fc[DAT_800d1c40].Boards[best].Stats[3];
			for (int r = 0; r < 4; r++) {
				int b = rows[r].bar;
				int x = rows[r].x;
				int y = rows[r].y - (bar[b]->m_h >> 1);
				for (i = 0; i < rows[r].value; i++) {
					bar[b]->draw(x, y, 0, -1, -1, -1);
					x += 15;
				}
				for (i = 0; i < bonus[r]; i++) {
					bar[4]->draw(x, y, 0, -1, -1, -1);
					x += 15;
				}
			}
			textTimer = 4;
		} else if (textTimer) {
			textTimer--;
			if (textTimer == 3) {
				bioRect1->restore(203, 287);
				bioRect2->restore(203, 320);
			}
			Mess_SetCurrentFont("stats1.fnt");
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(1);
			FUN_8001e114(203, 299 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[0]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[0]), DAT_800a44fc[DAT_800d1c40].pBio[0], 0, 0, 256, 0);
			FUN_8001e114(203, 320 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[1]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[1]), DAT_800a44fc[DAT_800d1c40].pBio[1], 0, 0, 256, 0);
			FUN_8001e114(203, 341 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[2]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[2]), DAT_800a44fc[DAT_800d1c40].pBio[2], 0, 0, 256, 0);
			FUN_8001e114(203, 362 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[3]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[3]), DAT_800a44fc[DAT_800d1c40].pBio[3], 0, 0, 256, 0);
			FUN_8001e114(203, 383 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[4]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[4]), DAT_800a44fc[DAT_800d1c40].pBio[4], 0, 0, 256, 0);
			FUN_8001e114(203, 404 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pBio[5]) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pBio[5]), DAT_800a44fc[DAT_800d1c40].pBio[5], 0, 0, 256, 0);
			if (textTimer == 0)
				medalTimer = 3;
		} else if (medalTimer) {
			Mess_SetCurrentFont("tapes1.fnt");
			SSkaterCareer *pCareer = &DAT_800a6844.Skater[DAT_800d1c40];
			*flags = pCareer->NumTapes;
			uint n = *flags;
			tapes[0] = n / 10 + '0';
			tapes[1] = n % 10 + '0';
			tapes[2] = 0;
			medalTimer--;
			tapesY = (Mess_TextHeight(tapes) >> 1) + 385 - FUN_8001db80(tapes);
			for (int c = 0; c < 3; c++) {
				int j = 0;
				while (FUN_8008f6fc(DAT_800a5398[j].Name, comps[c]))
					j++;
				*flags = pCareer->Medals[j];
				int f = *flags;
				if (f & 0x20)
					medalType[c] = 0;
				else if (f & 0x40)
					medalType[c] = 1;
				else if (f & 0x80)
					medalType[c] = 2;
				else
					medalType[c] = -1;
			}
		}

		switch (nameState) {
		case 0:
			Mess_SetCurrentFont("mainf.fnt");
			Mess_SetFontScale(255);
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(0);
			nameR = 320;
			nameX = -FUN_8001da44(DAT_800a44fc[DAT_800d1c40].pName) >> 1;
			nameStep = (nameR - nameX) / 6;
			nameState = 3;
			nameY = 70 - (Mess_TextHeight(DAT_800a44fc[DAT_800d1c40].pName) >> 1) + FUN_8001dc9c(DAT_800a44fc[DAT_800d1c40].pName);
			nameR -= nameStep;
			nameL = nameX - nameStep;
			break;
		case 3:
			nameX += nameStep;
			if ((nameX < nameL && nameX < nameR) || (nameL < nameX && nameR < nameX)) {
				statTimer = 5;
				nameState = 5;
			}
			nameBar->draw(0, 54, 0, -1, -1, -1);
			Mess_SetCurrentFont("mainf.fnt");
			Mess_SetFontScale(255);
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(0);
			FUN_8001e114(nameX, nameY, DAT_800a44fc[DAT_800d1c40].pName, 0, 0, 256, 0);
			break;
		case 4:
			nameX -= nameStep;
			if ((nameX < nameL && nameX < nameR) || (nameL < nameX && nameR < nameX))
				nameState = 5;
			nameBar->draw(0, 54, 0, -1, -1, -1);
			Mess_SetCurrentFont("mainf.fnt");
			Mess_SetFontScale(255);
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(0);
			FUN_8001e114(nameX, nameY, DAT_800a44fc[DAT_800d1c40].pName, 0, 0, 256, 0);
			break;
		case 5:
			nameBar->draw(0, 54, 0, -1, -1, -1);
			Mess_SetCurrentFont("mainf.fnt");
			Mess_SetFontScale(255);
			Mess_SetRGB(128, 128, 128, 0);
			FUN_8001d250(0);
			FUN_8001e114(nameX, nameY, DAT_800a44fc[DAT_800d1c40].pName, 0, 0, 256, 0);
			nameState = 2;
			break;
		case 1:
		case 2:
			break;
		}

		FUN_80061e00(400, 92, 183, 222);
		FUN_8005948c();
		FUN_8006b2f4();
		if (DAT_800c0a48[0].Start.Triggered || DAT_800c0a48[1].Start.Triggered ||
		    DAT_800c0a48[0].X.Triggered || DAT_800c0a48[1].X.Triggered) {
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			result = DAT_800d1c40;
			FUN_8004b250(145, 0x2000, 0);
			if (DAT_800a6844.LastSkater[0] != DAT_800d1c40) {
				DAT_800a6844.LastSkater[0] = 0;
				DAT_800a6844.LastDeck[0] = 0;
				DAT_800a6844.LastWheel[0] = 0;
				DAT_800a6844.LastTrucks[0] = 1;
				DAT_800a6844.m82c = 0;
			}
			DAT_800a6844.LastSkater[0] = DAT_800d1c40;
			goto done;
		}
		if (DAT_800c0a48[0].Triangle.Triggered || DAT_800c0a48[1].Triangle.Triggered) {
			result = -1;
			DAT_800c0a48[0].Triangle.Triggered = 0;
			DAT_800c0a48[1].Triangle.Triggered = 0;
			FUN_8004b250(147, 0x2000, 0);
			goto done;
		}
	}


done:
	FUN_8006af64();
	if (DAT_800d1afc)
		FUN_8004cdd0();
	FUN_8004d5d0(flags);
	if (DAT_800d2344)
		delete pBruce;
	FUN_800591c0();
	FUN_80059758();
	for (i = 0; i < 5; i++)
		delete bar[i];
	delete itemBox;
	delete itemBoxBack;
	for (i = 0; i < 3; i++)
		delete medal[i];
	for (i = 0; i < 4; i++)
		delete arrow[i];
	delete statBox;
	delete nameBar;
	delete topBox;
	delete bottomBox;
	delete bioRect1;
	delete bioRect2;
	DAT_800d1b10->unloadPRE("Player1.pre");
	Pack_DefragmentFully();
	Mess_SetCurrentFont("tapes1.fnt");
	Mess_UnloadFont();
	Mess_SetCurrentFont("stats1.fnt");
	Mess_UnloadFont();
	Mess_SetCurrentFont("mainf.fnt");
	return result;
}

/* FUN_8005bad0: the CBruce preview's screen-space limits (also in src/unnamed/8005bad0.c). The TU
   ends with the out-of-line copy of CItem's inline virtual destructor (FUN_8005bb3c, _._5CItem),
   whose vtable _vt.5CItem g++ puts in .rdata ahead of this TU's jump tables. */
extern "C" void FUN_8005bad0()
{
	DAT_800d2334 = (80 - DAT_800d1c50) * DAT_800d1c48;
	DAT_800d232c = DAT_800d1c48 * 171;
	DAT_800d2330 = (DAT_800d1c50 + 263) * DAT_800d1c48;
	DAT_800d2328 = (DAT_800d1c54 - 37) * DAT_800d1c4c;
}
