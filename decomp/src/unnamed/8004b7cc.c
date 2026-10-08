/* SFX_ModifyVol__FUiii (0x8004b7cc) */
#include "names.h"
typedef struct {
	int a, b;
	short c, d;
	char pad[48];
} S;

extern int DAT_800d13cc;

void FUN_80093e54(int a, S *s);

void SFX_ModifyVol(unsigned mask, int a, int b) {
	int i;
	S s;

	if (mask) {
		if (!(a < 16384))
			a = 16383;

		if (!(b < 16384))
			b = 16383;

		a = (a * DAT_800d13cc) >> 14;
		b = (b * DAT_800d13cc) >> 14;

		if (a < -16383)
			a = -16383;

		if (!(a < 16384))
			a = 16383;

		if (b < -16383)
			b = -16383;

		if (!(b < 16384))
			b = 16383;

		for (i = 0; i < 24; i++) {
			if (mask & (1 << i)) {
				s.a = i;
				s.b = 3;
				s.c = a;
				s.d = b;
				FUN_80093e54(i, &s);
			}
		}
	}
}
