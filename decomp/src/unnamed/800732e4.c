/* DeleteStuff__5CTape (0x800732e4) */
#include "names.h"
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	char pad[68];
	struct VT *vt;
};

void CTape_DeleteStuff(char *p) {
	struct O *o = *(struct O **)(p + 308);

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	*(int *)(p + 308) = 0;
}
