/* Suspend__5CBodyPP5CBody (0x80043a14) */
#include "names.h"
struct VT {
	char pad[56];
	short off;
	short pad2;
	void (*fn)(char *);
};

char DAT_800d19b4[8];

void CBody_DeleteFrom(char *p, char *q);
void CBody_AttachTo(char *p, char *q);

void CBody_Suspend(char *p, char *a) {
	struct VT *vt = *(struct VT **)(p + 72);

	vt->fn(p + vt->off);

	*(char **)(p + 76) = a;
	CBody_DeleteFrom(p, a);
	CBody_AttachTo(p, DAT_800d19b4);

	*(unsigned short *)(p + 82) |= 1;
}
