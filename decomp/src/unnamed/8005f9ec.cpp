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

extern int GPreferences[];
extern SControl Pad[2];
extern int SFXLEVEL;
extern int XALEVEL;
extern short GameFMV_StartX;

Sprite *DAT_800d1d5c;
Sprite *DAT_800d1d60;

extern "C" {
	int getSelected__12VerticalMenu(int);
	void FUN_8002357c(int);
	void SFX_PlayX__FUisi(int, int, int);
	void FUN_80023168(int);
	void FUN_80022aec(CVector *);
}

void Pad_ClearTriggers(SControl *);
void GameFMV_StopFMV(void);
void GameFMV_StartFMV(int);

extern "C" void FUN_8005f9ec(int a) {
	int v, w, u, i, dir;
	XALEVEL = getSelected__12VerticalMenu(a) == 1 ? GPreferences[1] * 0x555 : 0;
	SFXLEVEL = GPreferences[0] * 0x555;

	FUN_8002357c(0);

	if (Pad[0].Left.Triggered || Pad[1].Left.Triggered ||
	    Pad[0].Right.Triggered || Pad[1].Right.Triggered) {
		dir = 0;

		if (Pad[0].Left.Triggered || Pad[1].Left.Triggered)
			dir = 1;

		Pad_ClearTriggers(&Pad[0]);
		Pad_ClearTriggers(&Pad[1]);

		if (getSelected__12VerticalMenu(a) == 0) {
			w = GPreferences[0] + 1;

			if (dir)
				w = GPreferences[0] - 1;

			GPreferences[0] = w;

			if (w < 0)
				GPreferences[0] = 0;

			v = GPreferences[0];

			if (v >= 12) {
				GPreferences[0] = 12;
				v = 12;
			}

			SFXLEVEL = v * 0x555;
			SFX_PlayX__FUisi(145, 8192, 0);
		}

		if (getSelected__12VerticalMenu(a) == 1) {
			u = GPreferences[1] + 1;

			if (dir)
				u = GPreferences[1] - 1;

			GPreferences[1] = u;

			if (u < 0)
				GPreferences[1] = 0;

			if (GPreferences[1] >= 12)
				GPreferences[1] = 12;
		}
	}

	if (Pad[0].Start.Triggered || Pad[1].Start.Triggered ||
	    Pad[0].X.Triggered || Pad[1].X.Triggered) {
		if (getSelected__12VerticalMenu(a) == 0) {
			Pad_ClearTriggers(&Pad[0]);
			Pad_ClearTriggers(&Pad[1]);
			SFX_PlayX__FUisi(145, 8192, 0);
		}

		if (getSelected__12VerticalMenu(a) == 1) {
			Pad_ClearTriggers(&Pad[0]);
			Pad_ClearTriggers(&Pad[1]);
			GameFMV_StopFMV();
			CVector t(0, 0, 0);

			FUN_80023168(2);
			FUN_80022aec(&t);

			GameFMV_StartX = -1;
			GameFMV_StartFMV(0);
		}
	}

	for (i = 0; i < 12; i++) {
		v = 32;

		if (i < GPreferences[0])
			v = 128;

		DAT_800d1d5c->draw(i * 24 + 206, 204, 0, v, v, v);

		v = 32;

		if (i < GPreferences[1])
			v = 128;

		DAT_800d1d60->draw(i * 24 + 206, 284, 0, v, v, v);
	}
}
