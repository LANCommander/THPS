/* _._11CBackground (0x8007821c) */
#include "names.h"
extern char DAT_800a3494[];

char *DAT_800d1fe4;
unsigned short DAT_800d1fe8;

void CBody_DeleteFrom(char *, void *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__11CBackground(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a3494;
	CBody_DeleteFrom(t, &DAT_800d1fe4);

	DAT_800d1fe8--;
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
