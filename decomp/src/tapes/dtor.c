/* _._5CTape (0x80073228) */
#include "names.h"
extern char __vt_5CTape[];

extern void *PowerUpList __attribute__((section(".data")));
void CBody_DeleteFrom(char *, void *);
void CTape_DeleteStuff(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__5CTape(char *t, int f) {
	*(char **)(t + 0x48) = __vt_5CTape;
	CBody_DeleteFrom(t, &PowerUpList);
	CTape_DeleteStuff(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
