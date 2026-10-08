/* FUN_8004b038 (0x8004b038) */
struct S {
	int a;
	short b, c;
	int p1, p2;
	short h, i;
	int j, k;
	int l, m;
};

int DAT_800d1ad0;
int DAT_800d1ad4;
int DAT_800d1a94;
int DAT_800d1a98;

void FUN_80094d74(void);
void FUN_80094444(struct S *s);

void FUN_8004b038(void) {
	struct S s;

	FUN_80094d74();

	s.a = 963;
	s.b = 16383;
	s.c = 16383;
	s.h = 32512;
	s.i = 32512;
	s.j = 0;
	s.k = 1;
	FUN_80094444(&s);

	DAT_800d1ad0 = 0;
	DAT_800d1ad4 = 0;
	DAT_800d1a94 = -1;
	DAT_800d1a98 = -1;
}
