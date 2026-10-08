/* _._8CQuadBit (0x800283e0) */
#include "names.h"
extern char __vt_8CQuadBit[];

char QuadBitList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_800283e0(char *p, int f) {
	*(char **)(p + 68) = __vt_8CQuadBit;
	CBit_DeleteFrom(p, QuadBitList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
