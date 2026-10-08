/* _._11CSimpleAnim (0x80029920) */
extern char __vt_11CSimpleAnim[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80029920(char *p, int f) {
	*(char **)(p + 68) = __vt_11CSimpleAnim;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
