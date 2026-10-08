/* __10CRibbonBit (0x80029d80) */
#include "names.h"
extern char DAT_8009f6d0[];

void CLinked2EndedBit_ctor(char *, int);

char *CRibbonBit_ctor(char *this, int n) {
	CLinked2EndedBit_ctor(this, n);

	*(char **)(this + 0x44) = DAT_8009f6d0;
	return this;
}
