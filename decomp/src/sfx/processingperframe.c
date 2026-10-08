/* SFX_ProcessingPerFrame__Fv (0x8004bf30) */
int DAT_800d1aa8, DAT_800d1aac, DAT_800d1ac8;
unsigned char DAT_800d1ac0;
unsigned DAT_800d1abc, DAT_800d1aa4, DAT_800d1ab8, DAT_800d1ab0, DAT_800d1ab4;

void FUN_800947e4(int, int);
void FUN_80094c74(int, int);
void FUN_800947c4(int, short *);

void SFX_ProcessingPerFrame__Fv(void) {
	short st[4];
	int i;
	unsigned m;

	DAT_800d1abc = 0;

	if (DAT_800d1aa8) {
		FUN_800947e4(1, DAT_800d1aa8);

		DAT_800d1aa8 = 0;
	}

	if (DAT_800d1aac) {
		FUN_800947e4(0, DAT_800d1aac);

		DAT_800d1aac = 0;
	}

	if (DAT_800d1ac0) {
		FUN_80094c74(8, DAT_800d1ac8);

		DAT_800d1ac0 = 0;
	}

	for (i = 0; i < 24; i++) {
		m = 1 << i;

		if (DAT_800d1aa4 & m)
			continue;

		if (DAT_800d1ab8 & m)
			continue;

		FUN_800947c4(i, st);

		if (DAT_800d1ab0 & m) {
			if (st[0])
				continue;

			if (DAT_800d1ab4 & m)
				DAT_800d1ab0 &= ~m;
			else
				DAT_800d1ab4 |= m;
		} else {
			if (st[0] == 0)
				DAT_800d1abc |= m;
		}
	}

	DAT_800d1aa4 = 0;
}
