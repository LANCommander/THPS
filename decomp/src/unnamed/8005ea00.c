/* FUN_8005ea00 (0x8005ea00) */
struct S {
	int a, b, c;
};

extern struct S DAT_800a1cac;

void FUN_8005e0e0(struct S *t, struct S *z, int a, int b, int *p, int c, int d, int e, int f);

void FUN_8005ea00(int a) {
	struct S t = DAT_800a1cac;
	struct S z;

	z.a = 0;
	z.b = 0;
	z.c = 0;
	FUN_8005e0e0(&t, &z, 3, 32, &a, 0, 0, 0, 0);
}
