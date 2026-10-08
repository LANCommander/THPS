/* _._9CPolyLine (0x800271a0) */
#include "names.h"
extern char DAT_8009f670[];
extern int DAT_800d18f4;

void Mem_Delete(int a);
void CBit_DeleteFrom(char *p, int *q);
int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800271a0(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f670;
	Mem_Delete(*(int *)(p + 80));
	CBit_DeleteFrom(p, &DAT_800d18f4);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
