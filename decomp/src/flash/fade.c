/* Flash_Fade__Fii (0x8001f3b8) */
#include "names.h"
int DAT_800d1610, DAT_800d1614, DAT_800d1608, DAT_800d2210, DAT_800d220c, DAT_800d2208,
    DAT_800d2214;
unsigned char DAT_800d1604;

void Flash_Fade(int a, int b) {
	DAT_800d1610 = 1;
	DAT_800d1614 = a;
	DAT_800d1604 = 255;
	DAT_800d2210 = 0;
	DAT_800d220c = 0;
	DAT_800d2208 = 0;
	DAT_800d1608 = b;
	DAT_800d2214 = 0xff0000 / a;
}
