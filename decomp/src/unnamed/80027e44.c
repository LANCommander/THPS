/* FUN_80027e44 (0x80027e44) */
extern char DAT_8009f8b0[];

int DAT_800d1868;

char *FUN_80027e44(char *p) {
	char *q = p + 60;

	*(char **)(p + 68) = DAT_8009f8b0;
	p[60] = 1;
	q[1] = 1;
	q[2] = 1;
	DAT_800d1868 = DAT_800d1868 + 1;
	return p;
}
