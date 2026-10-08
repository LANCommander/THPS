/* GraffitiColor__FP6CBruce (0x8006ca1c) */
#include "names.h"
extern int DAT_800d16a4;
extern int DAT_800d17c8;

void Mess_SetRGB(unsigned char r, unsigned char g, unsigned char b, int a);

void GraffitiColor(int a) {
	if (DAT_800d16a4 == 8) {
		if (a == DAT_800d17c8)
			Mess_SetRGB(80, 80, 128, 0);
		else
			Mess_SetRGB(128, 80, 80, 0);
	}
}
