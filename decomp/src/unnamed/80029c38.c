/* _._5CFrag (0x80029c38) */
extern char __vt_5CFrag[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80029c38(char *p, int f) {
	*(char **)(p + 68) = __vt_5CFrag;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
