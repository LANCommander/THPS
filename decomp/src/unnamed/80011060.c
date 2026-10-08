/* FUN_80011060 (0x80011060) */
#include "names.h"
struct S {
	char pad[76];
	int f;
	char q[40];
};

extern struct S DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int Redbook_Rnd(int a);
void SFX_PlayLR(int a, int b, int c, int d);

void FUN_80011060(int a) {
	short s1, s0;

	if (DAT_800a5398[DAT_800d1e28].f && DAT_800d16a4 == 1) {
		s1 = (a * (Redbook_Rnd(20) + 90)) / 100;
		s0 = (a * (Redbook_Rnd(20) + 90)) / 100;
		SFX_PlayLR(50, s1, s0, 0);
	}
}
