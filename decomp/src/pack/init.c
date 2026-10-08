/* Pack_Init__Fv (0x80049780) */
#include "names.h"
int DAT_800d1a60, DAT_800d1a64, DAT_800d1a68, DAT_800d1a74, DAT_800d1a78;

void *Pack_NewFree(int, int, int, int);

void Pack_Init(void) {
	DAT_800d1a68 = 0;
	DAT_800d1a60 = 0;
	DAT_800d1a64 = 0;
	DAT_800d1a74 = 512;
	Pack_NewFree(512, 256, 512, 256);
	Pack_NewFree(512, 0, 512, 256);

	DAT_800d1a78 = 0;
}
