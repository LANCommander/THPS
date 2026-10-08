/* _._6CPixel (0x800294a8) */
#include "names.h"
extern char DAT_8009f7a0[];

char DAT_800d18d8[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_800294a8(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f7a0;
	CBit_DeleteFrom(p, DAT_800d18d8);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
