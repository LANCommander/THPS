/* FUN_800448b8 (0x800448b8) */
#include "names.h"
extern int DAT_800d2610[];

int *DAT_800d19f8;

void Mem_Delete(int *p);

void FUN_800448b8(void) {
	int i;
	int *p;
	int *n;

	for (i = 0; i < 256; i++)
		DAT_800d2610[i] = 0;

	for (p = DAT_800d19f8; p; p = n) {
		n = (int *)p[5];
		Mem_Delete(p);
	}

	DAT_800d19f8 = 0;
}
