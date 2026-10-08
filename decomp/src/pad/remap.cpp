/* Pad_Remap__Fv (0x80071588) */
/* C++ (PAD.CPP). Demo twin Pad_Remap (its extra swap block is gone in THPS1): copies each pad's
   face buttons out to the slots their remap pointers name. Inverse of Pad_Restore. */
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

extern SControl Pad[];

void Pad_Remap(void) {
	SButton TempButtonTriangle;
	SButton TempButtonX;
	SButton TempButtonCircle;
	SButton TempButtonSquare;

	{
		int i;

		for (i = 0; i < 2; i++) {
			TempButtonTriangle = Pad[i].Triangle;
			TempButtonCircle = Pad[i].Circle;
			TempButtonSquare = Pad[i].Square;
			TempButtonX = Pad[i].X;
			*Pad[i].pTriangle = TempButtonTriangle;
			*Pad[i].pCircle = TempButtonCircle;
			*Pad[i].pSquare = TempButtonSquare;
			*Pad[i].pX = TempButtonX;
		}
	}
}
