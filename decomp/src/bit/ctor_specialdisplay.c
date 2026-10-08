/* __15CSpecialDisplay (0x80027ec4) */
#include "names.h"
extern char __vt_15CSpecialDisplay[];

void *SpecialDisplayList;

char *CBit_ctor(char *);
void CBit_AttachTo(char *, void *);

char *CSpecialDisplay_ctor(char *t) {
	CBit_ctor(t);

	*(char **)(t + 0x44) = __vt_15CSpecialDisplay;
	CBit_AttachTo(t, &SpecialDisplayList);
	return t;
}
