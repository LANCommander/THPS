/* FUN_8005bb70 (0x8005bb70) */
/* C++ (front end). The front-end screen dispatcher, called once from FUN_8006b3f8 (after the boot
   init) and never returning. No demo twin (THPS2's FrontEnd2_Main is a different, table-driven
   design). Each pass:
     - (re)start: on a soft reset (START+SELECT, DAT_800d1cb8) unload everything and clear it; set
       DemoName to "demoA.rec" and clear the video-restart data.
     - top: in autotest mode (DAT_800d16a8) cycle level/skater/players and launch straight away.
       Otherwise, coming back from a game (DAT_800d1c9c = 1..6) jump straight back into the screen
       the player left from; else run the title screen (FUN_80060e98) and then the main menu
       (FUN_8005de7c).
     - main-menu choice: 3/4/17/18/19 = 1-player game modes -> skater select (FUN_80059794);
       33/34/35/1234567 = 2-player modes -> 2P skater select (FUN_80056754); 1553/1554 = replay
       the 1P/2P video restart; 99, 1569-1574, 25202-25207 = FMV movies; 100/101 = credits.
     - 1P: skater select -> board select (FUN_80054510); 2P: skater select -> board select
       (FUN_80051660); both then level select (FUN_8006658c). -1 from a screen backs up one.
     - launch: record the choice, start the game (FUN_8006b434 -> LaunchGame), tear down, reload
       the shell, and loop (rolling the credits first if the career was finished). */
enum EPackInitType { PACK_0, PACK_1 };
struct SVideoRestart {
	int NumSkaters;
	int Skater;
	int Skater2;
	int Level;
	int GGame;
};
struct SLevel {
	int pad0[3];
	int isCompetition;
	int pad10[26];
};
struct SDoubleBuffer {
	char pad0[0x80a8];
	unsigned char *Polys;	/* 0x80a8 */
};
struct SName {
	char c[10];
};

void Front_ClearGVideoRestartData();
void Mess_LoadFont(char *, int, int, int);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
void Mess_SetFontScale(unsigned);
void Mess_SetCurrentFont(char *);
void Mess_UnloadFont();
void Pack_DefragmentFully();
void Init_Restart(EPackInitType, int);
void Competition_Init();

extern "C" {
extern SVideoRestart DAT_800a42f4;	/* GVideoRestart */
extern SLevel DAT_800a5398[];		/* Levels */
extern unsigned char DAT_800a7068[];	/* last 1P skater */
extern SDoubleBuffer DAT_800a891c[2];	/* DB */
extern SName DAT_800bf0c4;		/* DemoName */
extern int DAT_800d13d8;		/* GRollCredits */
extern int DAT_800d16a4;		/* GGame */
extern int DAT_800d16a8;		/* autotest */
extern int DAT_800d16ac;
extern int DAT_800d16b0;
extern int DAT_800d16b4;
extern int DAT_800d16b8;
extern int DAT_800d16d8;		/* 2nd player's skater */
extern int DAT_800d1780;		/* GNumberOfPlayers */
extern int DAT_800d1d80;
extern int DAT_800d1dc0;
extern int DAT_800d1de8;		/* GVideoReplay */
extern int DAT_800d1e28;		/* GLevel */
extern SName DAT_800a192c;		/* "demoA.rec" */
extern char DAT_800a1938[];		/* DAT_800a1938 */
extern char DAT_800a1944[];		/* DAT_800a1944 */
extern char DAT_800a1950[];		/* DAT_800a1950 */
extern char DAT_800a195c[];		/* DAT_800a195c */

int DAT_800d1c9c;			/* screen to return to */
short DAT_800d1ca0;
int DAT_800d1cb0;			/* DemoTimer */
int DAT_800d1cb4;
int DAT_800d1cb8;			/* soft reset */

void FUN_80010000(void);
void FUN_800101e4(void);
short FUN_80014ba4(SName *);
void FUN_800161d8(void);
void FUN_800171f0(void);
void FUN_8001d250(int);
void FUN_8001f0dc(void);
void FUN_8001f1b4(int);
void FUN_80022c1c(int);
void FUN_800491e8(void);
void FUN_8004b09c(char *);
void FUN_8004d5d0(void *);
void FUN_8004fe28(int, int);
int FUN_80051660(int);
int FUN_80054510(int);
int FUN_80056754(void);
int FUN_80059794(void);
void FUN_8005c678(void);
void FUN_8005c734(int);
void FUN_8005c85c(void);
void FUN_8005c8ac(void);
void FUN_8005c8dc(int);
void FUN_8005ca10(void);
void FUN_8005ca88(void);
void FUN_8005cae8(void);
void FUN_8005d35c(int, int, int);
int FUN_8005de7c(int);
void FUN_80060e98(void);
void FUN_800642d4(int);
int FUN_8006658c(int);
void FUN_8006af64(void);
void FUN_8006b01c(int);
void FUN_8006b434(int, int);
void FUN_8005bb70(void);
}

static inline int GetReturnScreen()
{
	int s = DAT_800d1c9c;
	DAT_800d1c9c = 5;
	return s;
}

void FUN_8005bb70(void)
{
	int choice;
	int players;
	int mode;
	int skater;
	int menu;
	int r;

	FUN_8005c678();
	for (;;) {
		if (DAT_800d1cb8) {
reset:
			FUN_8001f0dc();
			FUN_8005ca10();
			FUN_8005cae8();
			FUN_8005c678();
		}
		DAT_800bf0c4 = DAT_800a192c;
		DAT_800d1cb4 = 1;
		Front_ClearGVideoRestartData();
		FUN_80010000();
		FUN_800161d8();
top:
		FUN_8005c8ac();
		DAT_800d1dc0 = 1;
		DAT_800d1780 = 1;
		DAT_800d1cb0 = 1600;
		FUN_800642d4(2);
		DAT_800d1ca0 = 0;
		if (DAT_800d16a8) {
			mode = 1;
			skater = DAT_800d16ac;
			choice = DAT_800d16b4;
			DAT_800d16d8 = DAT_800d16b0;
			if (!DAT_800d16b8) {
				DAT_800d1780 = 1;
				DAT_800d16a4 = 1;
				players = 1;
			} else {
				players = 2;
				DAT_800d1780 = 2;
				DAT_800d16a4 = 8;
			}
			if (++DAT_800d16ac == 11)
				DAT_800d16ac = 0;
			if (++DAT_800d16b4 == 9) {
				DAT_800d16b4 = 0;
				DAT_800d16b8 ^= 1;
				if (++DAT_800d16b0 == 11)
					DAT_800d16b0 = 0;
			}
			goto launch;
		}
		FUN_8005ca88();
		if (DAT_800d1c9c) {
			FUN_8005c734(157);
			Mess_LoadFont(DAT_800a1938, -1, -1, -1);
			Mess_SetRGB(128, 128, 128, 0);
			Mess_SetFontScale(256);
			FUN_8001d250(1);
			FUN_8001f1b4(4);
			mode = 0;
			skater = DAT_800a7068[0];
			players = 1;
			switch (DAT_800d16a4) {
			case 1:
				menu = 16;
				break;
			case 2:
			case 3:
				mode = 1;
				break;
			case 4:
				break;
			case 5:
			case 6:
				mode = 1;
				menu = 32;
				players = 2;
				break;
			case 7:
				mode = 5;
				menu = 32;
				players = 2;
				break;
			case 8:
				mode = 3;
				menu = 32;
				players = 2;
				break;
			}
			switch (GetReturnScreen()) {
			case 2:
				if (players != 1)
					goto board2;
				FUN_800642d4(1);
				goto board1;
			case 1:
				if (players == 1)
					FUN_800642d4(1);
				goto level;
			case 3:
				DAT_800a42f4.NumSkaters = 0;
				menu = 96;
				FUN_8005c8dc(0);
				goto mainmenu;
			case 4:
				DAT_800a42f4.NumSkaters = 0;
				menu = 0;
				FUN_8005c8dc(0);
				goto mainmenu;
			case 5:
				DAT_800a42f4.NumSkaters = 0;
				menu = 0;
				FUN_8005c8dc(0);
				goto mainmenu;
			case 6:
				if (players == 1)
					FUN_800642d4(1);
				choice = DAT_800d1e28;
				Mess_SetCurrentFont(DAT_800a1938);
				Mess_UnloadFont();
				FUN_8005cae8();
				goto launch;
			}
		}
		DAT_800d1c9c = 5;
title:
		FUN_8005ca10();
		FUN_80060e98();
		if (DAT_800d1cb8)
			goto reset;
		Mess_SetCurrentFont(DAT_800a1944);
		Mess_UnloadFont();
		if (!DAT_800d1cb0)
			goto demo;
		menu = 0;
mainmenu:
		FUN_8005c734(157);
		Pack_DefragmentFully();
		choice = FUN_8005de7c(menu);
		if (DAT_800d1cb8)
			goto reset;
		if (!DAT_800d1cb0)
			goto demo;
		FUN_800101e4();
		mode = 0;
		players = 1;
		menu = 0;
		switch (choice) {
		case -1:
			goto title;
		case 17:
		case 18:
			if (choice == 18) {
				DAT_800d1d80 = 0;
				FUN_80010000();
			}
			DAT_800d16a4 = players;
			menu = 16;
			goto skater1;
		case 3:
			DAT_800d16a4 = choice;
			mode = 1;
			goto skater1;
		case 4:
			DAT_800d16a4 = 2;
			mode = 1;
			goto skater1;
		case 34:
			mode = 1;
			DAT_800d16a4 = 5;
			menu = 32;
			players = 2;
			goto skater2;
		case 33:
			mode = 3;
			DAT_800d16a4 = 8;
			menu = 32;
			players = 2;
			goto skater2;
		case 1234567:
			mode = 1;
			DAT_800d16a4 = 6;
			menu = 32;
			players = 2;
			goto skater2;
		case 35:
			mode = 5;
			DAT_800d16a4 = 7;
			menu = 32;
			players = 2;
			goto skater2;
		case 1553:
			mode = 2;
			choice = DAT_800a42f4.Level;
			skater = DAT_800a42f4.Skater;
			DAT_800d1c9c = 3;
			DAT_800d16a4 = DAT_800a42f4.GGame;
			goto replay;
		case 1554:
			players = 2;
			mode = 2;
			choice = DAT_800a42f4.Level;
			skater = DAT_800a42f4.Skater2;
			DAT_800d1c9c = 3;
			DAT_800d16a4 = DAT_800a42f4.GGame;
			DAT_800d16d8 = DAT_800a42f4.Skater;
		replay:
			FUN_8005ca10();
			FUN_8005cae8();
			goto launch;
		case 19:
			DAT_800d1d80 = players;
			DAT_800d16a4 = players;
			menu = 16;
			goto skater1;
		case 100:
		case 101:
			goto credits;
		}
		if ((unsigned)(choice - 99) < 2 || (unsigned)(choice - 1569) < 6 || (unsigned)(choice - 25202) < 6)
			goto movie;
		goto title;

skater1:
		FUN_800642d4(1);
		DAT_800d1780 = 1;
		skater = FUN_80059794();
		if (DAT_800d1cb8)
			goto reset;
		if (skater == -1) {
			FUN_800642d4(2);
			goto mainmenu;
		}
		goto board1;
skater2:
		Pack_DefragmentFully();
		skater = FUN_80056754();
		if (DAT_800d1cb8)
			goto reset;
		Mess_SetCurrentFont(DAT_800a1950);
		Mess_UnloadFont();
		Mess_SetCurrentFont(DAT_800a1938);
		if (skater == -1)
			goto mainmenu;
		goto board2;
board1:
		r = FUN_80054510(skater);
		if (DAT_800d1cb8)
			goto reset;
		if (r == -1)
			goto skater1;
		goto level;
board2:
		r = FUN_80051660(skater);
		if (DAT_800d1cb8)
			goto reset;
		if (r == -1)
			goto skater2;
level:
		choice = FUN_8006658c(skater);
		if (DAT_800d1cb8)
			goto reset;
		if (choice == -1) {
			if (players == 1)
				goto board1;
			if (players == 2)
				goto board2;
		}
		Mess_SetCurrentFont(DAT_800a1938);
		Mess_UnloadFont();
		FUN_8005cae8();
launch:
		FUN_8001f0dc();
		FUN_8005ca10();
		FUN_8005d35c(choice, mode, skater);
		DAT_800d1780 = players;
		DAT_800d1dc0 = 0;
		if (!DAT_800d1de8 && DAT_800a5398[choice].isCompetition == 1)
			Competition_Init();
		FUN_8005c85c();
		FUN_8006b434(choice, skater);
		Init_Restart(PACK_0, 16);
		FUN_800491e8();
		DAT_800d1780 = 1;
		Init_Restart(PACK_1, 16);
		FUN_8006b01c(0);
		FUN_800161d8();
		FUN_8004b09c(DAT_800a195c);
		FUN_800171f0();
		if (DAT_800d1cb8) {
			DAT_800d1c9c = 0;
			continue;
		}
		if (!DAT_800d13d8)
			goto top;
		DAT_800d13d8 = 0;
		choice = 101;
		goto credits;

demo:
		do {
			FUN_80014ba4(&DAT_800bf0c4);
		} while (0);
		mode = 2;
		menu = 16;
		players = DAT_800a42f4.NumSkaters;
		skater = DAT_800a42f4.Skater;
		choice = DAT_800a42f4.Level;
		DAT_800d16d8 = DAT_800a42f4.Skater2;
		DAT_800d16a4 = DAT_800a42f4.GGame;
		FUN_8005cae8();
		DAT_800d1c9c = 4;
		goto launch;

movie:
		FUN_8006af64();
		DAT_800d1dc0 = 0;
		FUN_8005c85c();
		if ((unsigned)(choice - 99) < 2)
			menu = 96;
		else if ((unsigned)(choice - 1569) < 6)
			menu = 1568;
		else if ((unsigned)(choice - 25202) < 6)
			menu = 25200;
		switch (choice) {
		case 99: FUN_80022c1c(-26); break;
		case 1569: FUN_80022c1c(-25); break;
		case 1570: FUN_80022c1c(-12); break;
		case 1571: FUN_80022c1c(-13); break;
		case 1572: FUN_80022c1c(-14); break;
		case 1573: FUN_80022c1c(-15); break;
		case 1574: FUN_80022c1c(-16); break;
		case 25202: FUN_80022c1c(-17); break;
		case 25203: FUN_80022c1c(-18); break;
		case 25204: FUN_80022c1c(-19); break;
		case 25205: FUN_80022c1c(-20); break;
		case 25206: FUN_80022c1c(-21); break;
		case 25207: FUN_80022c1c(-11); break;
		case 100: break;
		}
		if (DAT_800a891c[0].Polys)
			FUN_8004d5d0(DAT_800a891c[0].Polys);
		DAT_800a891c[0].Polys = 0;
		FUN_8006b01c(1);
		FUN_8005c8dc(0);
		FUN_800161d8();
		goto mainmenu;


credits:
		FUN_8005c734(choice == 101 ? 157 : -1);
		FUN_8004fe28(choice != 100, 1);
		if (DAT_800a891c[0].Polys)
			FUN_8004d5d0(DAT_800a891c[0].Polys);
		DAT_800a891c[0].Polys = 0;
		FUN_8006b01c(1);
		FUN_8005c8dc(0);
		FUN_800161d8();
		DAT_800d16a4 = 3;
		goto top;
	}
}
