/* _._4CBit (0x80027e80) */
extern char DAT_8009f8b0[];

int DAT_800d1868;

int __dl__4CBitPv(void *p);

void FUN_80027e80(char *p, int f) {
	int t = DAT_800d1868;

	*(char **)(p + 68) = DAT_8009f8b0;
	DAT_800d1868 = t - 1;

	if (f & 1)
		__dl__4CBitPv(p);
}
