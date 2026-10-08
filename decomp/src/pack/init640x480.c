/* Pack_Init640x480__Fv (0x800497d4) */
#include "names.h"
int Pack_pFree, DAT_800d1a64, DAT_800d1a68, Pack_Width, LastPackInitType;

void *Pack_NewFree(int, int, int, int);

void Pack_Init640x480(void) {
	DAT_800d1a68 = 0;
	Pack_Width = 640;
	Pack_pFree = 0;
	DAT_800d1a64 = 0;
	Pack_NewFree(640, 256, 384, 256);
	Pack_NewFree(640, 0, 384, 256);

	LastPackInitType = 1;
}
