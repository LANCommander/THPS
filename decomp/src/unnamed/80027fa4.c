/* _._15CNonRenderedBit (0x80027fa4) */
#include "names.h"
extern char __vt_15CNonRenderedBit[];

char NonRenderedBitList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80027fa4(char *p, int f) {
	*(char **)(p + 68) = __vt_15CNonRenderedBit;
	CBit_DeleteFrom(p, NonRenderedBitList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
