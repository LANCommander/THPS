/* _._5CGlow (0x80028f28) */
#include "names.h"
extern char DAT_8009f800[];

char DAT_800d18e8[8];

void Mem_Delete(int a);
void CBit_DeleteFrom(char *p, char *q);
int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80028f28(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f800;
	Mem_Delete(*(int *)(p + 72));
	CBit_DeleteFrom(p, DAT_800d18e8);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
