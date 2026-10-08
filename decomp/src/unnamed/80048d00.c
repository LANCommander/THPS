/* FUN_80048d00 (0x80048d00) */
extern char DAT_800a891c[];

void FUN_80048d00(void) {
	char *p = DAT_800a891c;
	char *q = p + 32768;

	*(short *)(q + 272) = 0;
	*(short *)(p + 100) = 0;
	*(short *)(q + 274) = 0;
	*(short *)(p + 102) = 0;
}
