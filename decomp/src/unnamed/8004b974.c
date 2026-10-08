/* SFX_Unpause__Fv (0x8004b974) */
#include "names.h"
struct S {
	int a, b, c, d, e;
	short f;
	char pad[42];
};

int DAT_800d1a9c;

extern unsigned short DAT_800d2b8c[];

void FUN_80093e54(int a, struct S *s);
void FUN_8008f3a0(int a, int b);

void SFX_Unpause(void) {
	struct S s;
	int i;
	unsigned short *q;

	if (DAT_800d1a9c) {
		i = 0;
		q = DAT_800d2b8c;
		DAT_800d1a9c = 0;
		s.b = 16;

		for (; i < 24; i++) {
			s.f = *q;
			FUN_80093e54(i, &s);

			q++;
		}

		FUN_8008f3a0(12, 0);
	}
}
