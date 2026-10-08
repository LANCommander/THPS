/* __16CLinked2EndedBit (0x800293c8) */
#include "names.h"
extern char __vt_16CLinked2EndedBit[];

char Linked2EndedBitList[8];

char *CFT4Bit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CLinked2EndedBit_ctor(char *p) {
	CFT4Bit_ctor(p);

	*(char **)(p + 68) = __vt_16CLinked2EndedBit;
	CBit_AttachTo(p, Linked2EndedBitList);
	return p;
}
