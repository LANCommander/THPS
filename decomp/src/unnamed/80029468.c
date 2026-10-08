/* __6CPixel (0x80029468) */
#include "names.h"
extern char __vt_6CPixel[];

char PixelList[8];

char *CBit_ctor(char *p);
void CBit_AttachTo(char *p, char *q);

char *CPixel_ctor(char *p) {
	CBit_ctor(p);

	*(char **)(p + 68) = __vt_6CPixel;
	CBit_AttachTo(p, PixelList);
	return p;
}
