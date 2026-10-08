/* FUN_800206ac (0x800206ac) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short v;
	short pad[3];
} TS;

struct VT {
	char pad[0x38];
	short off;
	short pad2;
	void (*fn)(char *);
};

typedef struct G {
	char pad[0x42];
	unsigned char b42;
	char pad2[0x50 - 0x43];
	unsigned cnt;
	char pad3[0x5e - 0x54];
	unsigned char b5e;
} G;

typedef struct P {
	unsigned short fl;
	char pad[2];
	V v;
	char pad2[0x3a - 0x10];
	unsigned short type;
	char pad3[0x48 - 0x3c];
	struct VT *vt;
	char pad4[0xe8 - 0x4c];
	unsigned e8;
	char pad5[0x134 - 0xec];
	G *g;
	unsigned short w138;
	unsigned short w13a;
	char pad6[0x13d - 0x13c];
	unsigned char b13d;
} P;

typedef struct Q {
	char pad[0x1c];
	V *f1c;
} Q;

extern int DAT_800d1780;
extern Q *DAT_800d19a4;
extern int DAT_800d16e4;
extern char DAT_800c9670[];

void DoPhysics__8CPowerUp(P *);
void CreateBit__8CPowerUp(P *);
void FUN_800201c8(void);
G *__nw__4CBitUi(int);
G *__5CGlowUiUi(G *, int, int);
void SetCentreRGB__5CGlowUcUcUc(G *, unsigned char, unsigned char, unsigned char);
void SetFringeRGB__5CGlowUiUcUcUc(G *, unsigned, unsigned char, unsigned char, unsigned char);
void SetFringeWidth__5CGlowUiUi(G *, unsigned, unsigned);
void SetPos__4CBitRC7CVector(G *, V *);
void SetRGB__5CGlowUcUcUc(G *, unsigned char, unsigned char, unsigned char);
void SetRadialRGB__5CGlowiUcUcUc(G *, int, unsigned char, unsigned char, unsigned char);
void SetRadius__5CGlowi(G *, int);
unsigned Utils_CrapDist__FRC7CVectorT0(V *, V *);

void FUN_800206ac(P *p) {
	unsigned v;
	unsigned i;
	char *tb;
	int t, idx, m;
	G *g;
	G *lg;
	V *s3;
	int s0;

	FUN_800201c8();

	if (DAT_800d1780 == 1) {
		if (p->fl & 1)
			return;

		v = p->e8 < 8001;
		goto test;
	} else if ((p->fl & 0x41) == 0x41) {
		return;
	} else if (p->e8 >= 8001) {
		v = Utils_CrapDist__FRC7CVectorT0((V *)((char *)DAT_800d19a4->f1c + 4), &p->v) < 8001;
	test:
		if (!v) {
			p->vt->fn((char *)p + p->vt->off);
			return;
		}
	}

	DoPhysics__8CPowerUp(p);

	s3 = &p->v;

	if (p->b13d == 0)
		CreateBit__8CPowerUp(p);

	if (p->g == 0) {
		g = __nw__4CBitUi(104);

		if (g)
			g = __5CGlowUiUi(g, 4, 2);

		p->g = g;
		g->b5e = 1;
		SetCentreRGB__5CGlowUcUcUc(p->g, 0, 0, 0);
		SetRGB__5CGlowUcUcUc(p->g, 0, 0, 0);
		SetFringeRGB__5CGlowUiUcUcUc(p->g, 1, 0, 0, 0);
		SetRadius__5CGlowi(p->g, 0);

		p->g->b42 = 1;

		switch (p->type) {
			case 18:
				i = 0;
				lg = p->g;

				if (lg->cnt != 0) {
					do {
						if (i & 1)
							SetRadialRGB__5CGlowiUcUcUc(lg, i, 96, 96, 0);
						else
							SetRadialRGB__5CGlowiUcUcUc(p->g, i, 64, 64, 64);

						i++;
						lg = p->g;
					} while (i < lg->cnt);
				}

				SetRGB__5CGlowUcUcUc(p->g, 32, 0, 0);
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 1, 0, 0, 0);

				p->w138 = 10;
				p->w13a = 3;
				break;
			case 4:
			case 5:
			case 6:
			case 10:
			case 15:
				i = 0;
				lg = p->g;

				if (lg->cnt != 0) {
					do {
						if (i & 1)
							SetRadialRGB__5CGlowiUcUcUc(lg, i, 0, 0, 96);
						else
							SetRadialRGB__5CGlowiUcUcUc(p->g, i, 0, 0, 0);

						i++;
						lg = p->g;
					} while (i < lg->cnt);
				}

				SetRGB__5CGlowUcUcUc(p->g, 0, 0, 0);
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 1, 0, 0, 0);

				p->w138 = 60;
				p->w13a = 10;
				break;
			case 16:
				i = 0;
				lg = p->g;

				if (lg->cnt != 0) {
					do {
						if (i & 1)
							SetRadialRGB__5CGlowiUcUcUc(lg, i, 96, 96, 0);
						else
							SetRadialRGB__5CGlowiUcUcUc(p->g, i, 64, 64, 64);

						i++;
						lg = p->g;
					} while (i < lg->cnt);
				}

				SetRGB__5CGlowUcUcUc(p->g, 0, 0, 0);
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 1, 0, 0, 0);

				p->w138 = 60;
				p->w13a = 10;
				break;
			case 21:
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 0, 48, 48, 0);

				p->w138 = 60;
				p->w13a = 10;
				break;
			case 22:
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 0, 64, 32, 8);

				p->w138 = 60;
				p->w13a = 10;
				break;
			case 23:
				SetFringeRGB__5CGlowUiUcUcUc(p->g, 0, 48, 0, 0);

				p->w138 = 60;
				p->w13a = 10;
				break;
		}
	}

	SetPos__4CBitRC7CVector(p->g, s3);

	s0 = p->w138 + (p->w13a * ((short *)DAT_800c9670)[((DAT_800d16e4 * 600) & 0x3ff8) >> 1]) / 4096;
	SetFringeWidth__5CGlowUiUi(p->g, 0, s0);
	SetFringeWidth__5CGlowUiUi(p->g, 1, s0);
}
