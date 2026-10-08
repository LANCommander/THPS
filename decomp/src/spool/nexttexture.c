/* NextTexture__Fv (0x8006f0ac) */
#include "names.h"
typedef struct STexture {
	char pad[0x20];
	struct STexture *next;
} STexture;

extern STexture *DAT_800c01a8[];

int DAT_800d23c4;
STexture *DAT_800d23c8;

STexture *NextTexture(void) {
	STexture *t;

	if (DAT_800d23c4 >= 512)
		return 0;

	t = DAT_800d23c8;

	if (t) {
	again:
		DAT_800d23c8 = t->next;
		return t;
	}

	do {
		DAT_800d23c8 = t = DAT_800c01a8[++DAT_800d23c4];

		if (DAT_800d23c4 >= 512)
			return 0;
	} while (!t);

	goto again;
}
