/* FUN_80024fa4 (0x80024fa4) */
#include "names.h"
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

void BlackOut(int, int, int, int);
void Front_Display(void);
void Mess_SetTextJustify(int);
void Mess_DrawText(int, int, int, int, int, int, int);
void Flash_Display(void);
void Mick_Darken(void);
void Display_Viewport(char *, int);
void Ob_AI(int *, int);
void Font_Display(void);
void FUN_8006dc78(void);
short FUN_8007b0fc(int);
void Mess_Display(void);
void Mess_SetRGB(int, int, int, int);
void Mess_SetScale(int);

void FUN_80024fa4(void) {
	int f, a, b, c;

	if (DAT_800d16dc) {
		Mess_SetRGB(255, 0, 0, 0);
		Mess_SetScale(256);
		Mess_SetTextJustify(0);
		Mess_DrawText(256, 60, DAT_800d16dc, 0, 0, 256, 0);
	}

	DAT_800a6790.f0e = FUN_8007b0fc(DAT_800d2044);

	if (!(DAT_800d16fc && DAT_800d1728 == 0)) {
		Ob_AI(&DAT_800d2044, DAT_800d16fc);

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

			Display_Viewport((char *)&DAT_800a6790, 0);
			break;
		case 1:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 286;
				DAT_800d1ff8 = 118;
				DAT_800d1ffc = -140;
			}

			BlackOut(254, 0, 4, 240);
			Display_Viewport(DAT_800a67a4, 0);
			Display_Viewport(DAT_800a67b8, 1);
			break;
		case 2:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 450;
				DAT_800d1ff8 = 60;
				DAT_800d1ffc = -120;
			}

			BlackOut(0, 118, 512, 4);
			Display_Viewport(DAT_800a67cc, 0);
			Display_Viewport(DAT_800a67e0, 1);
			break;
		case 3:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 642;
				DAT_800d1ff8 = 32;
				DAT_800d1ffc = -172;
			}

			BlackOut(256, 0, 256, 120);
			BlackOut(0, 120, 256, 120);
			Display_Viewport(DAT_800a67f4, 0);
			Display_Viewport(DAT_800a6808, 1);
			break;
		case 4:
			f = DAT_800d16fc;

			if (f == 0) {
				DAT_800d1ff4 = 610;
				DAT_800d1ff8 = 0;
				DAT_800d1ffc = -200;
			}

			BlackOut(304, 0, 208, 88);
			BlackOut(0, 152, 208, 88);
			Display_Viewport(DAT_800a681c, 0);
			Display_Viewport(DAT_800a6830, 1);
			break;
	}

	Font_Display();
	FUN_8006dc78();
	Front_Display();
	Mess_Display();

	if (DAT_800d140c && DAT_800d13e8 != 33)
		Mick_Darken();
	else
		DAT_800d1738 = 0;

	Flash_Display();

	DAT_800d1730 = (DAT_800d1a54 & 0x7fffffff) - (DAT_800d1a48->f80a8 & 0x7fffffff);
}
