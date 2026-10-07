/* Options_RemapControllers__Fv (0x80010518) */
/* C++ (CAREER.CPP). Demo twin. Points each pad's pTriangle/pSquare/pCircle/pX at the button the career options map it to. */
struct SButton {
	unsigned char Pressed;
	unsigned char Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle;
	SButton Square;
	SButton Circle;
	SButton X;
	char pad40[0x15c - 0x40];
	SButton *pTriangle;
	SButton *pSquare;
	SButton *pCircle;
	SButton *pX;
};
struct SOptions {
	int SFXVolume;
	int MusicVolume;
	int OtherOptions[66];
	int AutoKickEnabled[2];
	int VibrationEnabled[2];
	int ControllerFunction[2][4];
};
struct SCareer {
	char pad0[0x830];
	SOptions Options;
};
extern SControl DAT_800c0a48[2];
extern SCareer DAT_800a6844;

void Options_RemapControllers()
{
	int padNum;
	for (padNum = 0; padNum < 2; padNum++) {
		SButton *b = &DAT_800c0a48[padNum].Triangle;
		int *f = DAT_800a6844.Options.ControllerFunction[padNum];
		int i;
		for (i = 0; i < 4; i++) {
			switch (f[i]) {
			case 0: DAT_800c0a48[padNum].pTriangle = b + i; break;
			case 1: DAT_800c0a48[padNum].pSquare = b + i; break;
			case 2: DAT_800c0a48[padNum].pCircle = b + i; break;
			case 3: DAT_800c0a48[padNum].pX = b + i; break;
			}
		}
	}
}
