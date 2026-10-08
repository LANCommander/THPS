/* FUN_800652e4 (0x800652e4) */
extern char DAT_800a2140[];

int FUN_800642e8(char **p, int a, int b, int c, int d, int e, int f, int g, int h);

char **FUN_800652e4(char **p, int a, int b, int c, int d, int e, int f, int g, int h) {
	FUN_800642e8(p, a, b, c, d, e, f, g, h);

	*p = DAT_800a2140;
	return p;
}
