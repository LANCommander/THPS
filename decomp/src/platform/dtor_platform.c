/* _._9CPlatform (0x8003d7a0) */
#include "names.h"
extern char DAT_800a013c[];

extern void *DAT_800d19b0 __attribute__((section(".data")));
void CBody_DeleteFrom(char *, void *);
void SFX_Stop(unsigned);
void __dt__6CBaddy(char *, int);
void __dl__5CItemPv(char *);

void __dt__9CPlatform(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a013c;
	CBody_DeleteFrom(t, &DAT_800d19b0);

	if (*(unsigned *)(t + 0x244)) {
		SFX_Stop(*(unsigned *)(t + 0x244));

		*(unsigned *)(t + 0x244) = 0;
	}

	__dt__6CBaddy(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
