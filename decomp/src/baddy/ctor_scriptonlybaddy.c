/* __16CScriptOnlyBaddyPsi (0x800411ac) */
extern char DAT_800a0218[];

extern int DAT_800d199c __attribute__((section(".data")));

void *DAT_800d1998;

void __6CBaddy(char *);
void FUN_800438dc(char *, void *);
short *SquirtPos__5CBodyPs(char *, short *);
short *SquirtAngles__5CBodyPs(char *, short *);

char *__16CScriptOnlyBaddyPsi(char *t, short *p, int id) {
	int x;

	__6CBaddy(t);

	x = DAT_800d199c;
	*(char **)(t + 0x48) = DAT_800a0218;
	*(int *)(t + 0x218) = x;
	p = SquirtPos__5CBodyPs(t, p);
	*(short **)(t + 0x1b0) = SquirtAngles__5CBodyPs(t, p);
	*(int *)(t + 0x230) = -1;
	t[0x19c] = 1;
	*(unsigned short *)(t + 0xe2) = id;
	*(unsigned short *)t |= 0x41;
	*(unsigned short *)(t + 0x52) &= ~0x10;
	FUN_800438dc(t, &DAT_800d1998);

	*(short *)(t + 0xe0) = 0;
	*(short *)(t + 0x3a) = 203;
	return t;
}
