/* _._5CTape (0x80073228) */
#include "names.h"
extern char DAT_800a3060[];

extern void *DAT_800d1618 __attribute__((section(".data")));
void CBody_DeleteFrom(char *, void *);
void CTape_DeleteStuff(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__5CTape(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a3060;
	CBody_DeleteFrom(t, &DAT_800d1618);
	CTape_DeleteStuff(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
