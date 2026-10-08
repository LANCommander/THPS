/* __16CLinked2EndedBit (0x800293c8) */
#include "names.h"
extern char DAT_8009f7b8[];

char DAT_800d18d4[8];

char *CFT4Bit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CLinked2EndedBit_ctor(char *p) {
	CFT4Bit_ctor(p);

	*(char **)(p + 68) = DAT_8009f7b8;
	CBit_AttachTo(p, DAT_800d18d4);
	return p;
}
