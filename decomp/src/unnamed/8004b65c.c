/* SFX_ModifyPos__FUiRC7CVectori (0x8004b65c) */
typedef struct {
	int id;
	int cmd;
	short l, r;
	char pad[8];
	short v;
	char pad2[42];
} S;

extern int DAT_800d13cc;

unsigned short DAT_800d2b5c[48];

void FUN_80093e54(int, S *);
unsigned Utils_CalculateSpatialAttenuation__FRC7CVectorii(void *, int, int);

void SFX_ModifyPos__FUiRC7CVectori(unsigned a, void *pos, int b) {
	S s;
	unsigned t, l, r;
	int i, y, v, d;
	unsigned short x;
	unsigned short *tab;

	if (a) {
		t = Utils_CalculateSpatialAttenuation__FRC7CVectorii(pos, 256, 12000);
		l = ((t & 0xfff) * DAT_800d13cc) >> 14;
		r = (((t >> 16) & 0xfff) * DAT_800d13cc) >> 14;

		if ((int)t < 0)
			l = -l;

		i = 0;
		tab = DAT_800d2b5c;

		for (; i < 24; i++) {
			if (a & (1 << i)) {
				s.id = i;
				s.cmd = 3;

				if ((int)l < -16383)
					l = -16383;

				if ((int)l >= 16384)
					l = 16383;

				if ((int)r < -16383)
					r = -16383;

				if ((int)r >= 16384)
					r = 16383;

				s.l = l;
				s.r = r;

				if (b) {
					x = *tab;
					s.cmd = 19;
					y = x - (x * b / 8192);

					if (x < y) {
						d = y - x;
						v = x + (x >> 1);

						if (v < d)
							y = v;
					}

					s.v = y;
				}

				FUN_80093e54(i, &s);
			}

			tab += 1;
		}
	}
}
