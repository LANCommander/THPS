/* FUN_80024fa4 (0x80024fa4) */
typedef struct {
	char pad[0x80a8];
	unsigned f80a8;
} B;

extern char DAT_800c0a48[];

typedef struct {
	char pad[14];
	short f0e;
} Z;

extern Z DAT_800a6790;
extern char DAT_800a67a4[];
extern char DAT_800a67b8[];
extern char DAT_800a67cc[];
extern char DAT_800a67e0[];
extern char DAT_800a67f4[];
extern char DAT_800a6808[];
extern char DAT_800a681c[];
extern char DAT_800a6830[];
extern int DAT_800d13e8;
extern int DAT_800d140c;
extern B *DAT_800d1a48;
extern unsigned DAT_800d1a54;
extern int DAT_800d2044;
extern int DAT_800d1ff4;
extern int DAT_800d1ff8;
extern int DAT_800d1ffc;

int DAT_800d16a4, DAT_800d16dc, DAT_800d16fc, DAT_800d1728, DAT_800d1730, DAT_800d1738,
    DAT_800d173c, DAT_800d1748, DAT_800d1780, DAT_800d1830;

void BlackOut__Fiiii(int, int, int, int);
void Front_Display__Fv(void);
void Mess_SetTextJustify__FUc(int);
void Mess_DrawText__FiiPCciUiib(int, int, int, int, int, int, int);
void Flash_Display__Fv(void);
void Mick_Darken__Fv(void);
void Display_Viewport__FP9SViewporti(char *, int);
void Ob_AI__FPP5CBody(int *, int);
void Font_Display__Fv(void);
void FUN_8006dc78(void);
short FUN_8007b0fc(int);
void Mess_Display__Fv(void);
void Mess_SetRGB__FUcUcUci(int, int, int, int);
void Mess_SetScale__Fi(int);

void FUN_80024fa4(void) {
	int f, a, b, c;

	if (DAT_800d16dc) {
		Mess_SetRGB__FUcUcUci(255, 0, 0, 0);
		Mess_SetScale__Fi(256);
		Mess_SetTextJustify__FUc(0);
		Mess_DrawText__FiiPCciUiib(256, 60, DAT_800d16dc, 0, 0, 256, 0);
	}

	DAT_800a6790.f0e = FUN_8007b0fc(DAT_800d2044);

	if (!(DAT_800d16fc && DAT_800d1728 == 0)) {
		Ob_AI__FPP5CBody(&DAT_800d2044, DAT_800d16fc);

		if (DAT_800d1728)
			goto L90;
	}

	if (DAT_800c0a48[240]) {
		if (DAT_800d1748) {
			DAT_800d1748 = 0;

			if (DAT_800d1780 == 2 && DAT_800d16a4 != 7) {
				if (++DAT_800d173c >= 4)
					DAT_800d173c = 0;
			} else
				DAT_800d1830 ^= 1;
		}
	} else
		DAT_800d1748 = 1;

	if (DAT_800c0a48[605]) {
		DAT_800c0a48[605] = 0;

		if (++DAT_800d173c >= 4)
			DAT_800d173c = 0;
	}
L90:
	if (DAT_800d1780 == 2 && DAT_800d173c == 0 && DAT_800d16a4 != 7)
		DAT_800d173c = 1;

	switch (DAT_800d173c) {
		case 0:
			f = DAT_800d16fc;

			if (f == 0) {
				if (DAT_800d1830) {
					c = 386;
					a = 30;
					DAT_800d1ff4 = c;
					b = -160;
				} else {
					c = 290;
					a = 150;
					DAT_800d1ff4 = c;
					b = -108;
				}

				DAT_800d1ff8 = a;
				DAT_800d1ffc = b;
			}

			Display_Viewport__FP9SViewporti((char *)&DAT_800a6790, 0);
			break;
		case 1:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 286;
				DAT_800d1ff8 = 118;
				DAT_800d1ffc = -140;
			}

			BlackOut__Fiiii(254, 0, 4, 240);
			Display_Viewport__FP9SViewporti(DAT_800a67a4, 0);
			Display_Viewport__FP9SViewporti(DAT_800a67b8, 1);
			break;
		case 2:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 450;
				DAT_800d1ff8 = 60;
				DAT_800d1ffc = -120;
			}

			BlackOut__Fiiii(0, 118, 512, 4);
			Display_Viewport__FP9SViewporti(DAT_800a67cc, 0);
			Display_Viewport__FP9SViewporti(DAT_800a67e0, 1);
			break;
		case 3:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 642;
				DAT_800d1ff8 = 32;
				DAT_800d1ffc = -172;
			}

			BlackOut__Fiiii(256, 0, 256, 120);
			BlackOut__Fiiii(0, 120, 256, 120);
			Display_Viewport__FP9SViewporti(DAT_800a67f4, 0);
			Display_Viewport__FP9SViewporti(DAT_800a6808, 1);
			break;
		case 4:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 610;
				DAT_800d1ff8 = 0;
				DAT_800d1ffc = -200;
			}

			BlackOut__Fiiii(304, 0, 208, 88);
			BlackOut__Fiiii(0, 152, 208, 88);
			Display_Viewport__FP9SViewporti(DAT_800a681c, 0);
			Display_Viewport__FP9SViewporti(DAT_800a6830, 1);
			break;
	}

	Font_Display__Fv();
	FUN_8006dc78();
	Front_Display__Fv();
	Mess_Display__Fv();

	if (DAT_800d140c && DAT_800d13e8 != 33)
		Mick_Darken__Fv();
	else
		DAT_800d1738 = 0;

	Flash_Display__Fv();

	DAT_800d1730 = (DAT_800d1a54 & 0x7fffffff) - (DAT_800d1a48->f80a8 & 0x7fffffff);
}
