/* FUN_80010ac0 (0x80010ac0) */
struct S {
	char pad[76];
	int f;
	char q[40];
};

struct A {
	int v;
	char pad[20];
};

extern struct S DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;
extern struct A DAT_800a42b8[];

void SFX_Stop__FUi(unsigned a);

void FUN_80010ac0(void) {
	int i;

	if (DAT_800a5398[DAT_800d1e28].f) {
		if (DAT_800d16a4 == 1) {
			for (i = 0; i < 1; i++) {
				if (DAT_800a42b8[i].v)
					SFX_Stop__FUi(DAT_800a42b8[i].v);

				DAT_800a42b8[i].v = 0;
			}
		}
	}
}
