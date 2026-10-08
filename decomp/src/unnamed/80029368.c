/* _._8CFlatBit (0x80029368) */
#include "names.h"
extern char __vt_8CFlatBit[];

char FlatBitList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80029368(char *p, int f) {
	*(char **)(p + 68) = __vt_8CFlatBit;
	CBit_DeleteFrom(p, FlatBitList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
