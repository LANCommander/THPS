/* _._6CPixel (0x800294a8) */
#include "names.h"
extern char __vt_6CPixel[];

char PixelList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_800294a8(char *p, int f) {
	*(char **)(p + 68) = __vt_6CPixel;
	CBit_DeleteFrom(p, PixelList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
