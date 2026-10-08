/* __15CNonRenderedBit (0x80027f64) */
#include "names.h"
extern char DAT_8009f878[];

char DAT_800d18cc[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CNonRenderedBit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = DAT_8009f878;
	CBit_AttachTo(p, DAT_800d18cc);
	return p;
}
