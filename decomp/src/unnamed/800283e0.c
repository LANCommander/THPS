/* _._8CQuadBit (0x800283e0) */
#include "names.h"
extern char DAT_8009f848[];

char DAT_800d18dc[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_800283e0(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f848;
	CBit_DeleteFrom(p, DAT_800d18dc);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
