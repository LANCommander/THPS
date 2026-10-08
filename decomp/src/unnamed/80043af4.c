/* KillShadow__5CBody (0x80043af4) */
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

void CBody_KillShadow(char *p) {
	struct O *o;

	*(unsigned short *)(p + 82) &= 0xfff7;
	o = *(struct O **)(p + 208);

	if (o) {
		o->vt->fn((char *)o + o->vt->off, 3);

		*(int *)(p + 208) = 0;
	}
}
