/* _._6CSpark (0x800297bc) */
extern char DAT_8009f788[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800297bc(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f788;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
