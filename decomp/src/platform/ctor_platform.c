/* __9CPlatformPsi (0x8003d6d8) */
#include "names.h"
extern char DAT_800a013c[];

extern void *DAT_800d19b0 __attribute__((section(".data")));
extern char *DAT_800d19f0 __attribute__((section(".data")));
extern int DAT_800d199c __attribute__((section(".data")));
void CBaddy_ctor(char *);
void CItem_InitItem(char *, char *);
void CBody_AttachTo(char *, void *);
short *CBody_SquirtPos(char *, short *);
short *CBody_SquirtAngles(char *, short *);

char *CPlatform_ctor(char *t, short *p, int id) {
	char *nm;
	int x;

	CBaddy_ctor(t);

	nm = DAT_800d19f0;
	x = DAT_800d199c;
	*(char **)(t + 0x48) = DAT_800a013c;
	*(int *)(t + 0x218) = x;
	CItem_InitItem(t, nm);
	CBody_AttachTo(t, &DAT_800d19b0);

	*(short *)(t + 0x22c) = 402;
	*(unsigned short *)t |= 0x111;
	*(unsigned short *)t &= ~2;
	p = CBody_SquirtPos(t, p);
	*(short **)(t + 0x1b0) = CBody_SquirtAngles(t, p);
	*(unsigned short *)(t + 0xe2) = id;
	*(int *)(t + 0x248) = -1;
	*(short *)(t + 0x1d4) = 32;
	t[0x19c] = 1;
	return t;
}
