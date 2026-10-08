/* Pack_Init__Fv (0x80049780) */
#include "names.h"
int Pack_pFree, DAT_800d1a64, DAT_800d1a68, Pack_Width, LastPackInitType;

void *Pack_NewFree(int, int, int, int);

void Pack_Init(void) {
	DAT_800d1a68 = 0;
	Pack_pFree = 0;
	DAT_800d1a64 = 0;
	Pack_Width = 512;
	Pack_NewFree(512, 256, 512, 256);
	Pack_NewFree(512, 0, 512, 256);

	LastPackInitType = 0;
}
