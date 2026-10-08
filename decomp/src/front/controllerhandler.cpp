/* FUN_8005eb78 (0x8005eb78) */
/* C++ (front end, THPS1-only; no demo twin). The per-frame handler of the CONTROLLER options menu:
   FUN_8005f6bc passes it to the generic menu runner FUN_8005e0e0, which calls it with the
   VerticalMenu every frame (and, seeing this handler, binds the menu input to player
   DAT_800d1d28's pad). Rows: 0-3 = TRIANGLE/SQUARE/CIRCLE/X (each row shows the function mapped
   to that button), 4 = VIBRATION, 5 = AUTOKICK, 6 = RESET TO DEFAULT, 7 = BACK.
     - Player 2 with no second pad: fake a triangle press on pad 2 so the menu backs out.
     - Up/down/X/start: the row that was just changed (DAT_800d2350) keeps its new function and any
       other button that had the same function takes over the changed button's old one, so the
       mapping stays a permutation; the snapshot DAT_800bf280 is updated, the other rows' labels
       refreshed and the mapping committed to the options (FUN_8005eb28).
     - Left/right on a button row cycles its function 0..3; on VIBRATION/AUTOKICK sets it
       (left = on) and rebuilds the "%s %s" label (AUTOKICK also changes button labels).
     - X/start on RESET TO DEFAULT restores the identity mapping and turns both options on.
   The four left/right button-row blocks index by the stored selection (`Function[sel]`,
   `DAT_800d2350 = sel`), which keeps retail's unfolded (&map + 4k) + pl*16 address and the s2
   copy of the selection. The row address is built column-first (`b = &map[0].Function[sel];
   f = b + pl * 4;`), which puts the DAT_800bf260 `lui` ahead of `sll pl,4`. `f` is a block-local
   (set once per pseudo), so alias.c knows its base is DAT_800bf260 and lets the reload of *f move
   above the DAT_800d2350 byte store; one function-wide `f` set four times loses its base value. */
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
	int Unk140[3];
	int Connected; /* 0x14c */
	int rest[7];
};

struct SOptions {
	int SFXVolume;
	int MusicVolume;
	int OtherOptions[66];
	int AutoKickEnabled[2];       /* 0x110 */
	int VibrationEnabled[2];      /* 0x118 */
	int ControllerFunction[2][4]; /* 0x120 */
};

struct SPadMap {
	int Function[4];
};

struct SText {
	char pad0[0x4c];
	char *Autokick; /* 0x4c */
	char pad50[0xf0 - 0x50];
	char *On;  /* 0xf0: "on <off>" */
	char *Off; /* 0xf4: "<on> off" */
	char pad8[0x100 - 0xf8];
	char *Vibration; /* 0x100 */
};

class VerticalMenu {
  public:
	int getSelected();
	void setString(int, char *);
};

extern SControl DAT_800c0a48[2]; /* Pad */
extern SOptions DAT_800a4118;
extern SPadMap DAT_800bf260[2]; /* edited mapping */
extern SPadMap DAT_800bf280[2]; /* mapping before the last change */
extern SText DAT_800a5d5c;
extern char DAT_800d1d40[]; /* "%s %s" */

int DAT_800d1d28;   /* player being configured */
uchar DAT_800d2350; /* row last changed with left/right */

void Pad_ClearTriggers(SControl *);
int SFX_PlayX(unsigned, short, int);

extern "C" {
	int FUN_8008b900(char *, char *, ...);
	char *FUN_8005ea74(int);
	void FUN_8005eb28(int);
	void FUN_8005eb78(VerticalMenu *);
}

void FUN_8005eb78(VerticalMenu *menu) {
	int pl = DAT_800d1d28;
	char buf[32];
	uchar left;
	int sel;

	if (pl == 1 && !DAT_800c0a48[1].Connected) {
		DAT_800c0a48[1].Triangle.Triggered = 1;
		return;
	}

	Pad_ClearTriggers(&DAT_800c0a48[1 - pl]);

	if (DAT_800c0a48[pl].Start.Triggered || DAT_800c0a48[pl].X.Triggered ||
	    DAT_800c0a48[pl].Up.Triggered || DAT_800c0a48[pl].Down.Triggered) {
		switch (DAT_800d2350) {
			case 0:
				if (DAT_800bf260[pl].Function[2] == DAT_800bf260[pl].Function[0])
					DAT_800bf260[pl].Function[2] = DAT_800bf280[pl].Function[0];

				if (DAT_800bf260[pl].Function[1] == DAT_800bf260[pl].Function[0])
					DAT_800bf260[pl].Function[1] = DAT_800bf280[pl].Function[0];

				if (DAT_800bf260[pl].Function[3] == DAT_800bf260[pl].Function[0])
					DAT_800bf260[pl].Function[3] = DAT_800bf280[pl].Function[0];

				break;
			case 1:
				if (DAT_800bf260[pl].Function[0] == DAT_800bf260[pl].Function[1])
					DAT_800bf260[pl].Function[0] = DAT_800bf280[pl].Function[1];

				if (DAT_800bf260[pl].Function[2] == DAT_800bf260[pl].Function[1])
					DAT_800bf260[pl].Function[2] = DAT_800bf280[pl].Function[1];

				if (DAT_800bf260[pl].Function[3] == DAT_800bf260[pl].Function[1])
					DAT_800bf260[pl].Function[3] = DAT_800bf280[pl].Function[1];

				break;
			case 2:
				if (DAT_800bf260[pl].Function[0] == DAT_800bf260[pl].Function[2])
					DAT_800bf260[pl].Function[0] = DAT_800bf280[pl].Function[2];

				if (DAT_800bf260[pl].Function[1] == DAT_800bf260[pl].Function[2])
					DAT_800bf260[pl].Function[1] = DAT_800bf280[pl].Function[2];

				if (DAT_800bf260[pl].Function[3] == DAT_800bf260[pl].Function[2])
					DAT_800bf260[pl].Function[3] = DAT_800bf280[pl].Function[2];

				break;
			case 3:
				if (DAT_800bf260[pl].Function[0] == DAT_800bf260[pl].Function[3])
					DAT_800bf260[pl].Function[0] = DAT_800bf280[pl].Function[3];

				if (DAT_800bf260[pl].Function[2] == DAT_800bf260[pl].Function[3])
					DAT_800bf260[pl].Function[2] = DAT_800bf280[pl].Function[3];

				if (DAT_800bf260[pl].Function[1] == DAT_800bf260[pl].Function[3])
					DAT_800bf260[pl].Function[1] = DAT_800bf280[pl].Function[3];

				break;
		}

		DAT_800bf280[pl].Function[0] = DAT_800bf260[pl].Function[0];
		DAT_800bf280[pl].Function[1] = DAT_800bf260[pl].Function[1];
		DAT_800bf280[pl].Function[2] = DAT_800bf260[pl].Function[2];
		DAT_800bf280[pl].Function[3] = DAT_800bf260[pl].Function[3];

		if (menu->getSelected() != 0)
			menu->setString(0, FUN_8005ea74(DAT_800bf260[pl].Function[0]));

		if (menu->getSelected() != 1)
			menu->setString(1, FUN_8005ea74(DAT_800bf260[pl].Function[1]));

		if (menu->getSelected() != 2)
			menu->setString(2, FUN_8005ea74(DAT_800bf260[pl].Function[2]));

		if (menu->getSelected() != 3)
			menu->setString(3, FUN_8005ea74(DAT_800bf260[pl].Function[3]));

		FUN_8005eb28(pl);
	}

	if (DAT_800c0a48[pl].Left.Triggered || DAT_800c0a48[pl].Right.Triggered) {
		left = DAT_800c0a48[pl].Left.Triggered;
		Pad_ClearTriggers(&DAT_800c0a48[0]);
		Pad_ClearTriggers(&DAT_800c0a48[1]);

		if ((sel = menu->getSelected()) == 0) {
			SFX_PlayX(144, 8192, 0);
			int *b = &DAT_800bf260[0].Function[sel];
			int *f = b + pl * 4;

			*f = *f + (left ? -1 : 1);

			if ((signed char)*f < 0)
				*f = 3;

			if (*f >= 4)
				*f = 0;

			DAT_800d2350 = sel;
			menu->setString(sel, FUN_8005ea74(*f));
		}

		if ((sel = menu->getSelected()) == 1) {
			SFX_PlayX(144, 8192, 0);
			int *b = &DAT_800bf260[0].Function[sel];
			int *f = b + pl * 4;

			*f = *f + (left ? -1 : 1);

			if ((signed char)*f < 0)
				*f = 3;

			if (*f >= 4)
				*f = 0;

			DAT_800d2350 = sel;
			menu->setString(sel, FUN_8005ea74(*f));
		}

		if ((sel = menu->getSelected()) == 2) {
			SFX_PlayX(144, 8192, 0);
			int *b = &DAT_800bf260[0].Function[sel];
			int *f = b + pl * 4;

			*f = *f + (left ? -1 : 1);

			if ((signed char)*f < 0)
				*f = 3;

			if (*f >= 4)
				*f = 0;

			DAT_800d2350 = sel;
			menu->setString(sel, FUN_8005ea74(*f));
		}

		if ((sel = menu->getSelected()) == 3) {
			SFX_PlayX(144, 8192, 0);
			int *b = &DAT_800bf260[0].Function[sel];
			int *f = b + pl * 4;

			*f = *f + (left ? -1 : 1);

			if ((signed char)*f < 0)
				*f = 3;

			if (*f >= 4)
				*f = 0;

			DAT_800d2350 = sel;
			menu->setString(sel, FUN_8005ea74(*f));
		}

		if (menu->getSelected() == 4) {
			if (left != DAT_800a4118.VibrationEnabled[pl])
				SFX_PlayX(144, 8192, 0);

			DAT_800a4118.VibrationEnabled[pl] = left != 0;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.Vibration,
			             DAT_800a4118.VibrationEnabled[pl] ? DAT_800a5d5c.On : DAT_800a5d5c.Off);
			menu->setString(4, buf);
		}

		if (menu->getSelected() == 5) {
			if (left != DAT_800a4118.AutoKickEnabled[pl])
				SFX_PlayX(144, 8192, 0);

			DAT_800a4118.AutoKickEnabled[pl] = left != 0;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.Autokick,
			             DAT_800a4118.AutoKickEnabled[pl] ? DAT_800a5d5c.On : DAT_800a5d5c.Off);
			menu->setString(5, buf);
			menu->setString(0, FUN_8005ea74(DAT_800bf260[pl].Function[0]));
			menu->setString(1, FUN_8005ea74(DAT_800bf260[pl].Function[1]));
			menu->setString(2, FUN_8005ea74(DAT_800bf260[pl].Function[2]));
			menu->setString(3, FUN_8005ea74(DAT_800bf260[pl].Function[3]));
		}
	}

	if (DAT_800c0a48[pl].Start.Triggered || DAT_800c0a48[pl].X.Triggered) {
		if (menu->getSelected() != 7) {
			Pad_ClearTriggers(&DAT_800c0a48[0]);
			Pad_ClearTriggers(&DAT_800c0a48[1]);
		}

		if (menu->getSelected() == 6) {
			DAT_800bf260[pl].Function[0] = 0;
			DAT_800bf260[pl].Function[1] = 1;
			DAT_800bf260[pl].Function[2] = 2;
			DAT_800bf260[pl].Function[3] = 3;
			FUN_8005eb28(pl);

			DAT_800a4118.VibrationEnabled[pl] = 1;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.Vibration, DAT_800a5d5c.On);
			menu->setString(4, buf);

			DAT_800a4118.AutoKickEnabled[pl] = 1;
			FUN_8008b900(buf, DAT_800d1d40, DAT_800a5d5c.Autokick, DAT_800a5d5c.On);
			menu->setString(5, buf);
			menu->setString(0, FUN_8005ea74(DAT_800bf260[pl].Function[0]));
			menu->setString(1, FUN_8005ea74(DAT_800bf260[pl].Function[1]));
			menu->setString(2, FUN_8005ea74(DAT_800bf260[pl].Function[2]));
			menu->setString(3, FUN_8005ea74(DAT_800bf260[pl].Function[3]));
		}

		if (menu->getSelected() != 4 && menu->getSelected() != 5)
			SFX_PlayX(145, 8192, 0);
	}
}
