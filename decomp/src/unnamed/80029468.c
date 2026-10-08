/* __6CPixel (0x80029468) */
#include "names.h"
extern char DAT_8009f7a0[];

char DAT_800d18d8[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CPixel_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = DAT_8009f7a0;
	CBit_AttachTo(p, DAT_800d18d8);
	return p;
}
