/* __9CPlatformPsi (0x8003d6d8) */
extern char DAT_800a013c[];

extern void *DAT_800d19b0 __attribute__((section(".data")));
extern char *DAT_800d19f0 __attribute__((section(".data")));
extern int DAT_800d199c __attribute__((section(".data")));
void __6CBaddy(char *);
void InitItem__5CItemPc(char *, char *);
void AttachTo__5CBodyPP5CBody(char *, void *);
short *SquirtPos__5CBodyPs(char *, short *);
short *SquirtAngles__5CBodyPs(char *, short *);

char *__9CPlatformPsi(char *t, short *p, int id) {
	char *nm;
	int x;

	__6CBaddy(t);

	nm = DAT_800d19f0;
	x = DAT_800d199c;
	*(char **)(t + 0x48) = DAT_800a013c;
	*(int *)(t + 0x218) = x;
	InitItem__5CItemPc(t, nm);
	AttachTo__5CBodyPP5CBody(t, &DAT_800d19b0);

	*(short *)(t + 0x22c) = 402;
	*(unsigned short *)t |= 0x111;
	*(unsigned short *)t &= ~2;
	p = SquirtPos__5CBodyPs(t, p);
	*(short **)(t + 0x1b0) = SquirtAngles__5CBodyPs(t, p);
	*(unsigned short *)(t + 0xe2) = id;
	*(int *)(t + 0x248) = -1;
	*(short *)(t + 0x1d4) = 32;
	t[0x19c] = 1;
	return t;
}
