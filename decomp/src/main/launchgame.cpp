/* LaunchGame__Fv (0x80026e98) */
/* C++ (MAIN.CPP). Fuzzy demo twin (0.30; THPS1 drops the attract-mode wait loop); locals and the
   DUN label from its MAIN.SYM. Re-initialises the packs keeping the save game across
   Init_ForGame, loads the game, then (unless a restart was requested) primes the pads and plays
   levels, looping back to DUN while the game mode says to carry on. */
typedef unsigned char uchar;

struct SPreferences {
	int p[6];
};

struct SSaveGame {
	int a[28];
	SPreferences Prefs; /* 0x70 */
};

struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};

struct SControl {
	SButton Triangle, Square, Circle, X;
	char pad40[364 - 64];
};

enum EPackInitType { PACK_0, PACK_1 };

extern SSaveGame DAT_800a5c64;
extern SControl DAT_800c0a48[2];
extern char DAT_8009f5b8[];
extern char DAT_8009f5cc[];
extern int DAT_800d1cf0;
extern int DAT_800d1cb0;
extern int DAT_800d1c9c;

int DAT_800d16a8;
int DAT_800d16a4;
int DAT_800d1780;
int DAT_800d1830;
int DAT_800d173c;
int DAT_800d16e0;
int DAT_800d17e8;
int DAT_800d17ec;
int DAT_800d17a8;

void Pack_Init();
void Init_Restart(EPackInitType, int);
void DumpAutoTest();
void Horse_Reset();
void Trig_ParseTRGFile();

extern "C" {
	void FUN_80071f3c(void);
	void FUN_800171e8(const SPreferences *);
	void FUN_8005cba0(void);
	void FUN_8001ccf8(SSaveGame *);
	void PlayAway__Fv(void);
	int FUN_8008c190(const char *, ...);
	void FUN_80071c24(int);
	void FUN_80025a88(void);
	void Trig_ExecuteRestart__Fv(void);
	void FUN_800491e8(void);
	void FUN_8006b01c(int);
}

int LaunchGame() {
	int Result = 0;

	Pack_Init();
	Init_Restart(PACK_0, 16);

	{
		SSaveGame tmp = DAT_800a5c64;

		FUN_80071f3c();

		DAT_800a5c64 = tmp;
	}

	FUN_800171e8(&DAT_800a5c64.Prefs);

	if (!Result) {
		FUN_8005cba0();

		if (DAT_800d16a8)
			DumpAutoTest();

		FUN_8001ccf8(&DAT_800a5c64);
	}

	if (DAT_800d1cf0) {
		if (DAT_800d1cb0)
			DAT_800d1c9c = 1;
		else
			DAT_800d1c9c = 4;

		DAT_800d1cf0 = 0;
		return 0;
	}

	if (DAT_800d16a4 == 7)
		Horse_Reset();
DUN:
	DAT_800c0a48[0].X.Pressed = 1;
	DAT_800c0a48[0].X.Triggered = 0;
	DAT_800c0a48[1].X.Pressed = 1;
	DAT_800c0a48[1].X.Triggered = 0;
	DAT_800d1830 = 0;
	DAT_800d173c = 0;

	if (DAT_800d1780 == 2 && DAT_800d16a4 != 7)
		DAT_800d173c = 1;

	PlayAway__Fv();

	DAT_800d17e8 = 0;
	DAT_800d17ec = 0;
	DAT_800d17a8 = 0;

	if (DAT_800d16e0 == 7) {
		FUN_8008c190(DAT_8009f5b8);
		FUN_80071c24(1);
		Trig_ParseTRGFile();
		FUN_80025a88();
		Trig_ExecuteRestart__Fv();
		goto DUN;
	}

	FUN_8008c190(DAT_8009f5cc);
	Init_Restart(PACK_0, 16);
	FUN_800491e8();

	DAT_800d1780 = 1;
	Init_Restart(PACK_1, 16);
	FUN_8006b01c(1);
	return 0;
}
