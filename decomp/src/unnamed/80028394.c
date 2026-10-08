/* __8CQuadBit (0x80028394) */
#include "names.h"
extern char DAT_8009f848[];

char DAT_800d18dc[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CQuadBit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = DAT_8009f848;
	*(int *)(p + 144) = 0x2c808080;
	CBit_AttachTo(p, DAT_800d18dc);
	return p;
}
