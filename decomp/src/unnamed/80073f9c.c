/* FUN_80073f9c (0x80073f9c) */
struct S {
	char pad[12];
	int f;
	char q[104];
};

extern struct S DAT_800a5398[];
extern unsigned char DAT_800a6850[];
extern char *DAT_800d17c8;

int FUN_80073f9c(void) {
	int c = 0;
	int i = 0;
	char *g = DAT_800d17c8;

	for (; i < 10; i++) {
		if (DAT_800a5398[i].f) {
			if (DAT_800a6850[i + *(int *)(g + 744) * 14] & 224)
				c++;
		}
	}

	return c == 3;
}
