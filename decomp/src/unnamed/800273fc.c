/* _._15CSmokeGenerator (0x800273fc) */
extern char DAT_8009f640[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_800273fc(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f640;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
