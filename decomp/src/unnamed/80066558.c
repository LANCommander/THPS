/* FUN_80066558 (0x80066558) */
extern char DAT_800a21b0[];

void FUN_80024238(void *p);

void FUN_80066558(char *p, int f) {
	*(char **)(p + 0) = DAT_800a21b0;

	if (f & 1)
		FUN_80024238(p);
}
