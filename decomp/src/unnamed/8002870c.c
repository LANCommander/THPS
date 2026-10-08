/* _._8CGenPoly (0x8002870c) */
#include "names.h"
extern char DAT_8009f830[];

char DAT_800d18e0[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_8002870c(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f830;
	CBit_DeleteFrom(p, DAT_800d18e0);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
