/* _._8CPowerUp (0x8001fe14) */
#include "names.h"
extern char __vt_8CPowerUp[];

void *PowerUpList;

void CBody_DeleteFrom(char *, void *);
void CPowerUp_DeleteStuff(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__8CPowerUp(char *t, int f) {
	*(char **)(t + 0x48) = __vt_8CPowerUp;
	CBody_DeleteFrom(t, &PowerUpList);
	CPowerUp_DeleteStuff(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
