/* _._6CMedal (0x80073c94) */
#include "names.h"
extern char __vt_6CMedal[];

void CMedal_DeleteStuff(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__6CMedal(char *t, int f) {
	*(char **)(t + 0x48) = __vt_6CMedal;
	CMedal_DeleteStuff(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
