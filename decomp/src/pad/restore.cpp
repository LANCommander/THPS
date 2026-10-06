/* Pad_Restore__Fv (0x8007171c) */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle;
	SButton Square;
	SButton Circle;
	SButton X;
	SButton LeftOne;
	SButton LeftTwo;
	SButton RightOne;
	SButton RightTwo;
	SButton Left;
	SButton Right;
	SButton Up;
	SButton Down;
	SButton AnalogueLeft;
	SButton AnalogueRight;
	SButton Start;
	SButton Select;
	SButton Crouch;
	SButton Jump;
	SButton SmartBomb;
	SButton SelectWeapon;
	uchar AnaloguePotMapping[4];
	uchar RawAnalogueMoveForwardsBackwards;
	uchar RawAnalogueMoveLeftRight;
	uchar RawAnalogueAimForwardsBackwards;
	uchar RawAnalogueAimLeftRight;
	char AnalogueMoveForwardsBackwards;
	char AnalogueMoveLeftRight;
	char AnalogueAimForwardsBackwards;
	char AnalogueAimLeftRight;
	int Type;
	uint ResetCounter;
	uchar Motor0;
	uchar Motor1;
	uchar Lock;
	uchar AlignCalled;
	ushort Motor0Timer;
	ushort Motor1Timer;
	SButton *pTriangle;
	SButton *pSquare;
	SButton *pCircle;
	SButton *pX;
};
extern SControl DAT_800c0a48[];
void Pad_Restore(void)
{
	SButton TempButtonTriangle;
	SButton TempButtonX;
	SButton TempButtonCircle;
	SButton TempButtonSquare;
	{
		int i;
		for (i = 0; i < 2; i++) {
			TempButtonTriangle = *DAT_800c0a48[i].pTriangle;
			TempButtonCircle = *DAT_800c0a48[i].pCircle;
			TempButtonSquare = *DAT_800c0a48[i].pSquare;
			TempButtonX = *DAT_800c0a48[i].pX;
			DAT_800c0a48[i].Triangle = TempButtonTriangle;
			DAT_800c0a48[i].Circle = TempButtonCircle;
			DAT_800c0a48[i].Square = TempButtonSquare;
			DAT_800c0a48[i].X = TempButtonX;
		}
	}
}
