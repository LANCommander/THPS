/* _._6CSpark (0x800297bc) */
extern char __vt_6CSpark[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800297bc(char *p, int f) {
	*(char **)(p + 68) = __vt_6CSpark;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
