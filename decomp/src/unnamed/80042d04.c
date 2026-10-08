/* FUN_80042d04 (0x80042d04) */
extern int DAT_800d140c;
extern int DAT_800d2044;
extern int DAT_800d1770;
extern int DAT_800d1998;
extern int DAT_800d1618;
extern int DAT_800d1718;
extern int DAT_800d1924;
extern int DAT_800d17c8;
extern int DAT_800d172c;
extern int DAT_800bf318[];
extern int DAT_800bf3d8[];
extern char DAT_800d25f0[];
extern char DAT_800a0524[];

typedef struct E {
	char p[0xc];
	int fc;
	int f10, f14;
	int f18, f1c, f20, f24;
	char q[0x154 - 0x28];
} E;

extern E DAT_800a44fc[];

char *DAT_800d19a4;

int FUN_8007cd64(int);
void Video_Record__FP6CBruce(char *);
void FUN_8006a930(char *);
void FUN_80042708(char *);
int FUN_8003b424(char *);
void HandleWater__6CBruce(char *);
void FUN_80042728(char *);
int FUN_80080cf8(char *, char *, int *, int, int);
void FUN_800427cc(char *, int);
void FUN_80020328(int, char *);
void DoShadowCheck__6CBruce(char *);
void GlowUpdate__6CBruce(char *);
void FUN_8008b900(char *, char *, int, int, int, int);
void Font_String__FUsUsPcUcUcUcUc(int, int, char *, int, int, int, int);

#define CC     (I(0x254) || DAT_800d172c)
#define I(o)   (*(int *)(a + (o)))
#define U8(o)  (*(unsigned char *)(a + (o)))
#define U16(o) (*(unsigned short *)(a + (o)))

void FUN_80042d04(char *a) {
	int sp20[4];
	int n2, n3, n4, n5, sx, sy, u, w, w2, w3, x1, x2, x3, x4, x5, x6, x7, d, t0, a2, a3, v2, e, *pp;
	char *s1;
	char *s2;
	char *p1;
	char *p2;

	if (DAT_800d140c == 0) {
		if (FUN_8007cd64(DAT_800d2044)) {
			I(0x330) = DAT_800d1770 + 0xe2e;
			return;
		}

		if (U8(0x890) == 0) {
			x1 = I(0x310);

			if (x1 && DAT_800d1770 - x1 >= 11)
				I(0x310) = 0;

			x2 = I(0x314);

			if (x2 && DAT_800d1770 - x2 >= 11)
				I(0x314) = 0;

			if (a == DAT_800d19a4)
				pp = DAT_800bf318;
			else
				pp = DAT_800bf3d8;

			x3 = *pp;

			switch (x3) {
				case 1:
					Video_Record__FP6CBruce(a);
					break;
				case 2:
					FUN_8006a930(a);
					return;
			}

			{
				I(0x6f0) = 100;
				I(0x20) = 0x404040;
				FUN_80042708(a);
				FUN_8003b424(a);
				HandleWater__6CBruce(a);

				if (((U16(0xe4) >> 1) ^ 1) & 1)
					U16(0x8fe) = U16(0x8fe) + 1;
				else {
					U16(0x8fe) = 0;
					U8(0x8fd) = 0;
				}

				if (U8(0x894) | U8(0x895)) {
					x4 = I(0x91c);

					if (x4 < 8)
						I(0x91c) = x4 + 1;
				} else {
					x5 = I(0x91c);

					if (x5)
						I(0x91c) = x5 - 1;
				}

				FUN_80042728(a);

				if (U8(0x8fc))
					U8(0x8fc) = U8(0x8fc) - 1;

				s2 = a + 0xf0;
				s1 = a + 4;
				x6 = FUN_80080cf8(s2, s1, sp20, DAT_800d1998, 0);

				if (x6)
					FUN_800427cc(a, x6);

				x7 = FUN_80080cf8(s2, s1, sp20, DAT_800d1618, 0);

				if (x7)
					FUN_80020328(x7, a);

				if (I(0x734) || (d = I(8) - I(0x2e4), ((d ^ (d >> 31)) - (d >> 31)) >= 65)) {
					I(0x2e4) = I(8);
					DoShadowCheck__6CBruce(a);
				} else {
					I(0xbc) = I(4);
					I(0xc4) = I(0xc);
				}

				GlowUpdate__6CBruce(a);

				if (*(short *)(a + 0xe6) < 0)
					*(short *)(a + 0xe6) = 0;

				if (DAT_800a44fc[I(0x2e8)].fc == 0x4000) {
					if (U16(0x146) != 0x3f)
						I(0x194) = I(0x194) | 0x1000;
					else
						I(0x194) = I(0x194) & ~0x1000;
				}

				if ((DAT_800d1718 || DAT_800d1924) && a == (char *)DAT_800d17c8) {
					a2 = DAT_800d1924;
					t0 = a2;
					p1 = DAT_800d25f0;
					p2 = DAT_800a0524;

					if (a2 == 0) {
						e = DAT_800a44fc[I(0x2e8)].f18;
						a2 = (*(unsigned char **)(a + 0x198))[0];

						if (CC) {
							w = a2 + 3;
							a2 = e + w;
						} else {
							n2 = e + a2;
							a2 = n2;
						}
					}

					a3 = t0;

					if (a3 == 0) {
						e = DAT_800a44fc[I(0x2e8)].f1c;
						a3 = (*(unsigned char **)(a + 0x198))[1];

						if (CC) {
							w2 = a3 + 3;
							a3 = e + w2;
						} else {
							n3 = e + a3;
							a3 = n3;
						}
					}

					FUN_8008b900(p1, p2, a2, a3, t0 ? t0 : ({
						             int e2 = DAT_800a44fc[I(0x2e8)].f20;
						             int u2 = (*(unsigned char **)(a + 0x198))[2];
						             int r2;

						             if (CC) {
							             r2 = u2 + 3;
							             n4 = e2 + r2;
							             r2 = n4;
						             } else
							             r2 = e2 + u2;

						             r2;
					             }),
					             DAT_800d1924 ? DAT_800d1924 : ({
						             int e3 = DAT_800a44fc[I(0x2e8)].f24;
						             int u3 = (*(unsigned char **)(a + 0x198))[3];
						             int r3;

						             if (CC) {
							             r3 = u3 + 3;
							             n5 = e3 + r3;
							             r3 = n5;
						             } else
							             r3 = e3 + u3;

						             r3;
					             }));
					Font_String__FUsUsPcUcUcUcUc(420, 200, DAT_800d25f0, 90, 90, 100, 0);
				}
			}
		}
	}
}
