/* _._15CSpecialDisplay (0x80027f04) */
#include "names.h"
extern char __vt_15CSpecialDisplay[];

void *SpecialDisplayList;

void CBit_DeleteFrom(char *, void *);
void FUN_80027e80(char *, int);
void __dl__4CBitPv(char *);

void __dt__15CSpecialDisplay(char *t, int f) {
	*(char **)(t + 0x44) = __vt_15CSpecialDisplay;
	CBit_DeleteFrom(t, &SpecialDisplayList);
	FUN_80027e80(t, 0);

	if (f & 1)
		__dl__4CBitPv(t);
}
