/* _._10CGPolyLine (0x80027334) */
#include "names.h"
extern char __vt_10CGPolyLine[];
extern int GPolyLineList;

void Mem_Delete(int a);
void CBit_DeleteFrom(char *p, int *q);
int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80027334(char *p, int f) {
	*(char **)(p + 68) = __vt_10CGPolyLine;
	Mem_Delete(*(int *)(p + 76));
	CBit_DeleteFrom(p, &GPolyLineList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
