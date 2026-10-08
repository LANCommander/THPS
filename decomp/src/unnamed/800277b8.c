/* _._11CGrindSpark (0x800277b8) */
extern char __vt_11CGrindSpark[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800277b8(char *p, int f) {
	*(char **)(p + 68) = __vt_11CGrindSpark;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
