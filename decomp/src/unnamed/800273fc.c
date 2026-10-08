/* _._15CSmokeGenerator (0x800273fc) */
extern char __vt_15CSmokeGenerator[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800273fc(char *p, int f) {
	*(char **)(p + 68) = __vt_15CSmokeGenerator;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
