/* __7CFT4Bit (0x80028004) */
#include "names.h"
extern char DAT_8009f860[];

char *CBit_ctor(char *p);

char *CFT4Bit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = DAT_8009f860;
	*(short *)(p + 92) = 128;
	*(short *)(p + 94) = 400;
	*(int *)(p + 76) = 0x2c808080;
	return p;
}
