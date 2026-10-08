/* __15CNonRenderedBit (0x80027f64) */
#include "names.h"
extern char __vt_15CNonRenderedBit[];

char NonRenderedBitList[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CNonRenderedBit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = __vt_15CNonRenderedBit;
	CBit_AttachTo(p, NonRenderedBitList);
	return p;
}
