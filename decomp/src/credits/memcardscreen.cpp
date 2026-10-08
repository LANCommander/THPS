/* FUN_80060ba0 (0x80060ba0) */
/* C++ (front end, THPS1-only; no demo twin). Runs the memory-card screen modally: sets up the
   card menus and a 640-byte block buffer, then loops the front-end frame (Front_MemCardHiResDisplay
   + Front_MemCardUpdate) until the update stops returning 18 (stay). Afterwards it clears the
   pads, plays the back sound, wipes both buffers, frees the menu and the buffer, reloads the
   options, clamps the volumes and copies the pad mapping. Returns -1 (39: cancelled), 19 (35)
   or 0. Called by FUN_800601fc and FUN_8005e8e0.
   Codegen: the exit code is inside the for(;;) as `if (r != 18) { ...; break; }`, which is why
   retail hoists &DAT_800c0a48 and the 35 into s-registers before the loop. */
typedef unsigned long ulong;
typedef unsigned int uint;
enum EMemCardState { MEMCARD_STATE_15 = 15 };
enum EPausedStatus { PAUSED_STATUS_39 = 39 };

struct SButton {
	unsigned char Pressed;
	unsigned char Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};

struct SControl {
	SButton Triangle, Square, Circle, X;
	char pad40[0x16c - 0x40];
};

struct SOptions {
	int SFXVolume;
	int MusicVolume;
	int OtherOptions[66];
	int AutoKickEnabled[2];
	int VibrationEnabled[2];
	int ControllerFunction[2][4]; /* 0x120 */
};

struct SVideoInfo {
	int VideoMode;
	ulong *pBlockStart;
	char pad8[0xc0 - 8];
};

struct SVideoSettings {
	int NumSkaters, Skater, Skater2, Level, GGame;
};

struct SCareer {
	int Version;
	char pad4[0x830 - 4];
};

struct SPadMap {
	int Function[4];
};

class VerticalMenu {
  public:
	void erase();
};

extern SCareer DAT_800a6844;
extern SControl DAT_800c0a48[2];
extern SVideoInfo DAT_800bf318;
extern SVideoSettings DAT_800a42f4;
extern SOptions DAT_800a4118;
extern SPadMap DAT_800bf260[2];
extern VerticalMenu *DAT_800d1104;

int DAT_800d2358;
int DAT_800d235c;

int Mess_GetFontScale();
void Mess_SetFontScale(uint);
void Pack_DefragmentFully();
void Pad_ClearTriggers(SControl *);
int SFX_PlayX(uint, short, int);
void Front_InitMemCardMenus(int, EMemCardState, EPausedStatus);
void Front_MemCardHiResDisplay();
int Front_MemCardUpdate();
void Front_RestoreBackground();

extern "C" {
	void *Mem_NewX__FUiii(uint, int, int);
	void FUN_8004d5d0(void *);
	void FUN_80011628(int);
	void FUN_8005c780(void);
	void FUN_8005c934(void);
	void FUN_80070ff4(void);
	void FUN_8006b240(void);
	void FUN_80061ea0(void);
	void FUN_80064890(VerticalMenu *, int, int);
	void FUN_8006b26c(void);
	void FUN_80011570(void);
	void FUN_80011150(void);
	void FUN_800103a4(void);
	int DrawSync(int);
}

int FUN_80060ba0() {
	int scale;
	int r;
	int ret;
	int i;

	scale = Mess_GetFontScale();
	DAT_800a6844.Version = 0xdeadbeef;
	Pack_DefragmentFully();
	Front_InitMemCardMenus(640, MEMCARD_STATE_15, PAUSED_STATUS_39);
	FUN_80011628(2);

	DAT_800bf318.pBlockStart = (ulong *)Mem_NewX__FUiii(640, 0, 1);
	DAT_800a42f4.NumSkaters = 0;

	for (;;) {
		FUN_8005c780();
		FUN_8005c934();
		FUN_80070ff4();
		FUN_8006b240();
		FUN_80061ea0();

		if (DAT_800d1104)
			FUN_80064890(DAT_800d1104, DAT_800d2358, DAT_800d235c);

		Front_MemCardHiResDisplay();
		FUN_8006b26c();

		r = Front_MemCardUpdate();

		if (r != 18) {
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			SFX_PlayX(145, 8192, 0);
			Mess_SetFontScale(scale);

			if (r == 39)
				ret = -1;
			else if (r == 35)
				ret = 19;
			else
				ret = 0;

			break;
		}
	}

	for (i = 0; i < 2; i++) {
		FUN_8006b240();
		FUN_80061ea0();
		Front_RestoreBackground();

		if (DAT_800d1104)
			DAT_800d1104->erase();

		FUN_8006b26c();
	}

	DrawSync(0);
	FUN_80011570();

	if (DAT_800d1104)
		FUN_80011150();

	FUN_8004d5d0(DAT_800bf318.pBlockStart);
	FUN_800103a4();

	if (DAT_800a4118.SFXVolume > 12)
		DAT_800a4118.SFXVolume = 12;

	if (DAT_800a4118.MusicVolume > 12)
		DAT_800a4118.MusicVolume = 12;

	for (int p = 0; p < 2; p++) {
		DAT_800bf260[p].Function[0] = DAT_800a4118.ControllerFunction[p][0];
		DAT_800bf260[p].Function[2] = DAT_800a4118.ControllerFunction[p][2];
		DAT_800bf260[p].Function[1] = DAT_800a4118.ControllerFunction[p][1];
		DAT_800bf260[p].Function[3] = DAT_800a4118.ControllerFunction[p][3];
	}

	return ret;
}
