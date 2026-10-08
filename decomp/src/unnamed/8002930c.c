/* __8CFlatBit (0x8002930c) */
#include "names.h"
extern char __vt_8CFlatBit[];

char FlatBitList[8];

char *CFT4Bit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CFlatBit_ctor(char *p) {
	CFT4Bit_ctor(p);

	*(char **)(p + 68) = __vt_8CFlatBit;
	CBit_AttachTo(p, FlatBitList);

	p[109] = 32;
	*(short *)(p + 102) = 1;
	*(int *)(p + 104) = 0x10001000;
	return p;
}
