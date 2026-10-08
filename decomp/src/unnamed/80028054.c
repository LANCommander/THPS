/* _._7CFT4Bit (0x80028054) */
extern char __vt_7CFT4Bit[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80028054(char *p, int f) {
	*(char **)(p + 68) = __vt_7CFT4Bit;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
