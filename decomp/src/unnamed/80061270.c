/* FUN_80061270 (0x80061270) */
#include "names.h"
int DAT_800d1d84;
int DAT_800d1d88;
short DAT_800d1d8c, DAT_800d1d8e;

extern char DAT_800a200c[], DAT_800a2024[], DAT_800a2048[];

void FUN_8006b240(void);
void FUN_80061ea0(void);
void Sprite_draw(int, int, int, int, int, int, int);
void Mess_SetRGB(int, int, int, int);
void Mess_SetTextJustify(int);
void FUN_8001f1b4(int);
void Mess_SetFontScale(int);
void Mess_DrawText(int, int, char *, int, int, int, int);
void FUN_8006b26c(void);
void FUN_8008eebc(int);

void FUN_80061270(int a) {
	int i;

	if (a != DAT_800d1d84) {
		DAT_800d1d84 = a;

		for (i = 0; i < 2; i++) {
			FUN_8006b240();
			FUN_80061ea0();
			Sprite_draw(DAT_800d1d88, DAT_800d1d8c, DAT_800d1d8e, 0, -1, -1, -1);
			Mess_SetRGB(128, 128, 128, 0);
			Mess_SetTextJustify(0);
			FUN_8001f1b4(4);

			if (a == 0) {
				Mess_SetFontScale(192);
				Mess_DrawText(320, 357, DAT_800a200c, 1, 0, 256, 0);
			} else if (a == 1) {
				Mess_SetFontScale(144);
				Mess_DrawText(320, 341, DAT_800a2024, 1, 0, 256, 0);
				Mess_DrawText(320, 373, DAT_800a2048, 1, 0, 256, 0);
			}

			FUN_8006b26c();
		}

		Mess_SetFontScale(255);
		FUN_8008eebc(0);
	}
}
