/* GotoStartOfTextureList__Fv (0x8006f094) */
#include "names.h"
int DAT_800d23c4;
int DAT_800d23c8;

extern int DAT_800c01a8[];

void GotoStartOfTextureList(void) {
	DAT_800d23c4 = 0;
	DAT_800d23c8 = DAT_800c01a8[0];
}
