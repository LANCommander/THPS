/* _._11EraseSprite (0x80063db4) */
#include "names.h"
extern char __vt_11EraseSprite[];
extern char DAT_800a21b0[];

void Mem_Delete(int a);
void __dl__6CClassPv(void *p);

void FUN_80063db4(char **p, int f) {
	*p = __vt_11EraseSprite;
	Mem_Delete(((int *)p)[3]);

	*p = DAT_800a21b0;

	if (f & 1)
		__dl__6CClassPv(p);
}
