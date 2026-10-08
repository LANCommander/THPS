/* __16CScriptOnlyBaddyPsi (0x800411ac) */
#include "names.h"
extern char DAT_800a0218[];

extern int DAT_800d199c __attribute__((section(".data")));

void *DAT_800d1998;

void CBaddy_ctor(char *);
void CBody_AttachTo(char *, void *);
short *CBody_SquirtPos(char *, short *);
short *CBody_SquirtAngles(char *, short *);

char *CScriptOnlyBaddy_ctor(char *t, short *p, int id) {
	int x;

	CBaddy_ctor(t);

	x = DAT_800d199c;
	*(char **)(t + 0x48) = DAT_800a0218;
	*(int *)(t + 0x218) = x;
	p = CBody_SquirtPos(t, p);
	*(short **)(t + 0x1b0) = CBody_SquirtAngles(t, p);
	*(int *)(t + 0x230) = -1;
	t[0x19c] = 1;
	*(unsigned short *)(t + 0xe2) = id;
	*(unsigned short *)t |= 0x41;
	*(unsigned short *)(t + 0x52) &= ~0x10;
	CBody_AttachTo(t, &DAT_800d1998);

	*(short *)(t + 0xe0) = 0;
	*(short *)(t + 0x3a) = 203;
	return t;
}
