/* FUN_80063db4 (0x80063db4) */
extern char DAT_800a2180[];
extern char DAT_800a21b0[];

void Mem_Delete__FPv(int a);
void FUN_80024238(void *p);

void FUN_80063db4(char **p, int f) {
	*p = DAT_800a2180;
	Mem_Delete__FPv(((int *)p)[3]);

	*p = DAT_800a21b0;

	if (f & 1)
		FUN_80024238(p);
}
