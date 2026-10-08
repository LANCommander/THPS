/* __8CFlatBit (0x8002930c) */
#include "names.h"
extern char DAT_8009f7d0[];

char DAT_800d18d0[8];

char *CFT4Bit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CFlatBit_ctor(char *p) {
	CFT4Bit_ctor(p);

	*(char **)(p + 68) = DAT_8009f7d0;
	CBit_AttachTo(p, DAT_800d18d0);

	p[109] = 32;
	*(short *)(p + 102) = 1;
	*(int *)(p + 104) = 0x10001000;
	return p;
}
