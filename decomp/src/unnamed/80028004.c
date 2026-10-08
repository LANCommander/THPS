/* __7CFT4Bit (0x80028004) */
#include "names.h"
extern char __vt_7CFT4Bit[];

char *CBit_ctor(char *p);

char *CFT4Bit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = __vt_7CFT4Bit;
	*(short *)(p + 92) = 128;
	*(short *)(p + 94) = 400;
	*(int *)(p + 76) = 0x2c808080;
	return p;
}
