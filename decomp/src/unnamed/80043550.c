/* __5CItem (0x80043550) */
extern char DAT_800a05f4[];
extern char DAT_800c5acc[];

char *__5CItem(char *p) {
	short *q = (short *)(p + 36);

	*(char **)(p + 72) = DAT_800a05f4;
	q[0] = 4096;
	q[1] = 4096;
	q[2] = 4096;
	*(char **)(p + 60) = DAT_800c5acc;
	return p;
}
