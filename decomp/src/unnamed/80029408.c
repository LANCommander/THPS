/* _._16CLinked2EndedBit (0x80029408) */
#include "names.h"
extern char __vt_16CLinked2EndedBit[];

char Linked2EndedBitList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80029408(char *p, int f) {
	*(char **)(p + 68) = __vt_16CLinked2EndedBit;
	CBit_DeleteFrom(p, Linked2EndedBitList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
