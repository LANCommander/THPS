/* __8CQuadBit (0x80028394) */
#include "names.h"
extern char __vt_8CQuadBit[];

char QuadBitList[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CQuadBit_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = __vt_8CQuadBit;
	*(int *)(p + 144) = 0x2c808080;
	CBit_AttachTo(p, QuadBitList);
	return p;
}
