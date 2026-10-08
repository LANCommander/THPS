/* _._5CGlow (0x80028f28) */
#include "names.h"
extern char __vt_5CGlow[];

char GlowList[8];

void Mem_Delete(int a);
void CBit_DeleteFrom(char *p, char *q);
int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80028f28(char *p, int f) {
	*(char **)(p + 68) = __vt_5CGlow;
	Mem_Delete(*(int *)(p + 72));
	CBit_DeleteFrom(p, GlowList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
