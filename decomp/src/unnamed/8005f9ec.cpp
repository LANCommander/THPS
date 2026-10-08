/* FUN_8005f9ec (0x8005f9ec) */
typedef unsigned char uchar;

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
	uchar AnaloguePotMapping[4];
	uchar Raw[4];
	char Analogue[4];
	int Type;
	int pad150[7];
};

struct CVector {
	int vx, vy, vz;
	CVector(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
};

class Sprite {
  public:
	void draw(int, int, int, int, int, int);
};

extern int DAT_800a4118[];
extern SControl DAT_800c0a48[2];
extern int DAT_800d13cc;
extern int DAT_800d13d0;
extern short DAT_800d1658;

Sprite *DAT_800d1d5c;
Sprite *DAT_800d1d60;

extern "C" {
	int FUN_8006516c(int);
	void FUN_8002357c(int);
	void FUN_8004b250(int, int, int);
	void FUN_80023168(int);
	void FUN_80022aec(CVector *);
}

void Pad_ClearTriggers(SControl *);
void GameFMV_StopFMV(void);
void GameFMV_StartFMV(int);

extern "C" void FUN_8005f9ec(int a) {
	int v, w, u, i, dir;
	DAT_800d13d0 = FUN_8006516c(a) == 1 ? DAT_800a4118[1] * 0x555 : 0;
	DAT_800d13cc = DAT_800a4118[0] * 0x555;

	FUN_8002357c(0);

	if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered ||
	    DAT_800c0a48[0].Right.Triggered || DAT_800c0a48[1].Right.Triggered) {
		dir = 0;

		if (DAT_800c0a48[0].Left.Triggered || DAT_800c0a48[1].Left.Triggered)
			dir = 1;

		Pad_ClearTriggers(&DAT_800c0a48[0]);
		Pad_ClearTriggers(&DAT_800c0a48[1]);

		if (FUN_8006516c(a) == 0) {
			w = DAT_800a4118[0] + 1;

			if (dir)
				w = DAT_800a4118[0] - 1;

			DAT_800a4118[0] = w;

			if (w < 0)
				DAT_800a4118[0] = 0;

			v = DAT_800a4118[0];

			if (v >= 12) {
				DAT_800a4118[0] = 12;
				v = 12;
			}

			DAT_800d13cc = v * 0x555;
			FUN_8004b250(145, 8192, 0);
		}

		if (FUN_8006516c(a) == 1) {
			u = DAT_800a4118[1] + 1;

			if (dir)
				u = DAT_800a4118[1] - 1;

			DAT_800a4118[1] = u;

			if (u < 0)
				DAT_800a4118[1] = 0;

			if (DAT_800a4118[1] >= 12)
				DAT_800a4118[1] = 12;
		}
	}

	if (DAT_800c0a48[0].Start.Triggered || DAT_800c0a48[1].Start.Triggered ||
	    DAT_800c0a48[0].X.Triggered || DAT_800c0a48[1].X.Triggered) {
		if (FUN_8006516c(a) == 0) {
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			FUN_8004b250(145, 8192, 0);
		}

		if (FUN_8006516c(a) == 1) {
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
			GameFMV_StopFMV();
			CVector t(0, 0, 0);

			FUN_80023168(2);
			FUN_80022aec(&t);

			DAT_800d1658 = -1;
			GameFMV_StartFMV(0);
		}
	}

	for (i = 0; i < 12; i++) {
		v = 32;

		if (i < DAT_800a4118[0])
			v = 128;

		DAT_800d1d5c->draw(i * 24 + 206, 204, 0, v, v, v);

		v = 32;

		if (i < DAT_800a4118[1])
			v = 128;

		DAT_800d1d60->draw(i * 24 + 206, 284, 0, v, v, v);
	}
}
