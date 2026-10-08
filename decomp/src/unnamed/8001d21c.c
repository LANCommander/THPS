/* FUN_8001d21c (0x8001d21c) */
extern char DAT_8009e548[];

void FUN_80024238(void *p);

void FUN_8001d21c(char *p, int f) {
	*(char **)(p + 0) = DAT_8009e548;

	if (f & 1)
		FUN_80024238(p);
}
