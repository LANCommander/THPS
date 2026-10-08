/* _._6CBaddy (0x8003faa8) */
extern char DAT_800a0270[];

int DAT_800d1988;

void SFX_Stop__FUi(unsigned);
void __dt__6CSuper(char *, int);
void __dl__5CItemPv(char *);

void __dt__6CBaddy(char *t, int f) {
	int c = DAT_800d1988;
	unsigned s = *(unsigned *)(t + 0x210);

	*(char **)(t + 0x48) = DAT_800a0270;
	DAT_800d1988 = c - 1;

	if (s)
		SFX_Stop__FUi(s);

	__dt__6CSuper(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
