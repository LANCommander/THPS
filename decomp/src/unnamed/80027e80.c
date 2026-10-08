/* _._4CBit (0x80027e80) */
extern char __vt_4CBit[];

int BitCount;

int __dl__4CBitPv(void *p);

void FUN_80027e80(char *p, int f) {
	int t = BitCount;

	*(char **)(p + 68) = __vt_4CBit;
	BitCount = t - 1;

	if (f & 1)
		__dl__4CBitPv(p);
}
