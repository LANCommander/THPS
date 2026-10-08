/* FUN_8007401c (0x8007401c) */
struct S {
	char pad[12];
	int f;
	char q[104];
};

extern struct S DAT_800a5398[];
extern unsigned char DAT_800a6850[];
extern char *DAT_800d17c8;

int FUN_8007401c(void) {
	int c = 0;
	int i = 0;
	char *g = DAT_800d17c8;

	for (; i < 10; i++) {
		if (DAT_800a5398[i].f) {
			if (DAT_800a6850[i + *(int *)(g + 744) * 14] & 32)
				c++;
		}
	}

	return c == 3;
}
