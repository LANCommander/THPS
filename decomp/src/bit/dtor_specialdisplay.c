/* _._15CSpecialDisplay (0x80027f04) */
#include "names.h"
extern char DAT_8009f890[];

void *DAT_800d18f0;

void CBit_DeleteFrom(char *, void *);
void FUN_80027e80(char *, int);
void __dl__4CBitPv(char *);

void __dt__15CSpecialDisplay(char *t, int f) {
	*(char **)(t + 0x44) = DAT_8009f890;
	CBit_DeleteFrom(t, &DAT_800d18f0);
	FUN_80027e80(t, 0);

	if (f & 1)
		__dl__4CBitPv(t);
}
