/* _._8CGenPoly (0x8002870c) */
#include "names.h"
extern char __vt_8CGenPoly[];

char GenPolyList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_8002870c(char *p, int f) {
	*(char **)(p + 68) = __vt_8CGenPoly;
	CBit_DeleteFrom(p, GenPolyList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
