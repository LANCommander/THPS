/* FUN_8006b630 (0x8006b630) */
#include "names.h"
extern char DAT_800a233c[];
extern char DAT_800d1998[];

void CBody_DeleteFrom(char *p, char *q);
int BASEF(char *p, int a);
void __dl__5CItemPv(void *p);

void FUN_8006b630(char *p, int f) {
	*(char **)(p + 72) = DAT_800a233c;
	CBody_DeleteFrom(p, DAT_800d1998);
	BASEF(p, 0);

	if (f & 1)
		__dl__5CItemPv(p);
}
