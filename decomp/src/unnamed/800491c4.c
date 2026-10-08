/* FUN_800491c4 (0x800491c4) */
extern char DAT_800a891c[];

void FUN_800491c4(void) {
	char *p = DAT_800a891c;
	char *q = p + 32768;
	char *r = p + 65536;

	*(int *)(q + 168) = 0;
	*(int *)(r + 340) = 0;
}
