/* __5CItem (0x80043550) */
#include "names.h"
extern char __vt_5CItem[];
extern char M3d_DefaultLight[];

char *CItem_ctor(char *p) {
	short *q = (short *)(p + 36);

	*(char **)(p + 72) = __vt_5CItem;
	q[0] = 4096;
	q[1] = 4096;
	q[2] = 4096;
	*(char **)(p + 60) = M3d_DefaultLight;
	return p;
}
