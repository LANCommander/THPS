/* FUN_80010f70 (0x80010f70) */
#include "names.h"
struct S {
	char pad[76];
	int f;
	char q[40];
};

extern struct S DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int DAT_800d10ec;

void SFX_PlayX(int a, int b, int c);

void FUN_80010f70(int a) {
	int s;

	if (DAT_800a5398[DAT_800d1e28].f && DAT_800d16a4 == 1) {
		if (a < 100)
			DAT_800d10ec += 2;
		else
			DAT_800d10ec = 0;

		s = (a << 14) / 1000;

		if (s > 16384)
			s = 16384;

		if (s < 4096)
			s = 4096;
		else
			SFX_PlayX(46, (short)(s / 2), 0);

		SFX_PlayX(47, (short)s, 0);
	}
}
