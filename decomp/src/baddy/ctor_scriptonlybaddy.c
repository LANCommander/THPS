/* __16CScriptOnlyBaddyPsi (0x800411ac) */
#include "names.h"
extern char __vt_16CScriptOnlyBaddy[];

extern int pCurrentPlayer __attribute__((section(".data")));

void *BaddyList;

void CBaddy_ctor(char *);
void CBody_AttachTo(char *, void *);
short *CBody_SquirtPos(char *, short *);
short *CBody_SquirtAngles(char *, short *);

char *CScriptOnlyBaddy_ctor(char *t, short *p, int id) {
	int x;

	CBaddy_ctor(t);

	x = pCurrentPlayer;
	*(char **)(t + 0x48) = __vt_16CScriptOnlyBaddy;
	*(int *)(t + 0x218) = x;
	p = CBody_SquirtPos(t, p);
	*(short **)(t + 0x1b0) = CBody_SquirtAngles(t, p);
	*(int *)(t + 0x230) = -1;
	t[0x19c] = 1;
	*(unsigned short *)(t + 0xe2) = id;
	*(unsigned short *)t |= 0x41;
	*(unsigned short *)(t + 0x52) &= ~0x10;
	CBody_AttachTo(t, &BaddyList);

	*(short *)(t + 0xe0) = 0;
	*(short *)(t + 0x3a) = 203;
	return t;
}
