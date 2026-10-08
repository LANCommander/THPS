/* FUN_8004eba0 (0x8004eba0) */
extern char DAT_800a1308[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_8004eba0(char *p, int f) {
	*(char **)(p + 68) = DAT_800a1308;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
