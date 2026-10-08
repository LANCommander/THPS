/* __15CSpecialDisplay (0x80027ec4) */
#include "names.h"
extern char DAT_8009f890[];

void *DAT_800d18f0;

char *CBit_ctor(char *);
void CBit_AttachTo(char *, void *);

char *CSpecialDisplay_ctor(char *t) {
	CBit_ctor(t);

	*(char **)(t + 0x44) = DAT_8009f890;
	CBit_AttachTo(t, &DAT_800d18f0);
	return t;
}
