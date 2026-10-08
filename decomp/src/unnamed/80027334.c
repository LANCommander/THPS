/* _._10CGPolyLine (0x80027334) */
#include "names.h"
extern char DAT_8009f658[];
extern int DAT_800d18f8;

void Mem_Delete(int a);
void CBit_DeleteFrom(char *p, int *q);
int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80027334(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f658;
	Mem_Delete(*(int *)(p + 76));
	CBit_DeleteFrom(p, &DAT_800d18f8);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
