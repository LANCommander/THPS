/* Competition_ResetMarquee__Fv (0x8007657c) */
typedef unsigned char uchar;
struct Msg { int a; int b; char pad[120 - 8]; };
struct Slot { char r10a; char r30a; char r10b; char r30b; };
struct Comp {
	char p0[4];
	uchar A[10];
	char p1[2];
	int f10, f14, f18;
	char p2[0x2c - 0x1c];
	struct { uchar a, b, c, d; int pad; } S[5];
	char p3[0x5c - 0x54];
	uchar D[10];
	char p4[0x66 - 0x66];
	uchar C[10];
	char p5[0x70 - 0x70];
	short Aa[10][3];
	short B[10];
	char p6[0xc0 - 0xc0];
	uchar flag;
	char p7[0xd4 - 0xc1];
	char *ptr;
	char buf[0x124 - 0xd8];
	int f124, f128, f12c;
};
extern Comp DAT_800c0fdc;
extern int DAT_800d1a20, DAT_800d1114;
extern const int DAT_800d1e28;
extern Msg DAT_800a5398[];
extern char DAT_800a3240[];
short DAT_800d1fc0, DAT_800d1fc2, DAT_800d1fc4, DAT_800d1fc6, DAT_800d1fc8;
void Redbook_InitialRand(int);
int Redbook_Rnd(int);
extern "C" void FUN_8008b900(char *, char *, int, int, int);

void Competition_ResetMarquee()
{
	Comp *c = &DAT_800c0fdc;
	int n;
	if (c->flag == 0) {
		c->f10 = 0;
		c->f14 = 0;
		c->f18 = 0;
		c->f12c = 0;
		Redbook_InitialRand(DAT_800d1a20);
		{
			int i;
			for (i = 0; i < 10; i++) c->A[i] = i;
		}
		n = DAT_800d1114;
		c->f128 = n;
		if (n == 10) {
			c->f128 = Redbook_Rnd(10);
			c->A[c->f128] = n;
		}
		if (DAT_800d1e28 == 8) {
			DAT_800d1fc0 = 975;
			DAT_800d1fc2 = 935;
			DAT_800d1fc4 = 910;
			DAT_800d1fc6 = 860;
			DAT_800d1fc8 = 770;
		} else {
			DAT_800d1fc0 = 975;
			DAT_800d1fc2 = 920;
			DAT_800d1fc4 = 870;
			DAT_800d1fc6 = 820;
			DAT_800d1fc8 = 520;
		}
		{
			uchar i;
			for (i = 0; i < 5; i++) {
				c->S[i].a = Redbook_Rnd(10);
				c->S[i].c = Redbook_Rnd(10);
				c->S[i].b = Redbook_Rnd(30);
				c->S[i].d = Redbook_Rnd(30);
			}
		}
		{
			uchar i;
			for (i = 0; i < 10; i++) {
				uchar j;
				for (j = 0; j < 3; j++) c->Aa[i][j] = 0;
				c->B[i] = 0;
				c->C[i] = i;
			}
		}
		c->flag = 0;
		{
			int i;
			for (i = 0; i < 10; i++) c->D[i] = 255;
		}
		{
			int i;
			for (i = 0; i < 10; i++) {
				int k, j, slot;
				slot = Redbook_Rnd(10 - i);
				j = 0;
				k = -1;
				while (slot >= j) {
					k++;
					if (c->D[k] == 255) j++;
				}
				c->D[k] = i;
			}
		}
		{
			int i;
			for (i = 0; i < 10; i++)
				if (c->D[i] == 9) c->D[i] = c->D[c->f128];
		}
		c->D[c->f128] = 255;
	}
	c->f124 = 0;
	c->ptr = 0;
	FUN_8008b900(c->buf, DAT_800a3240, DAT_800a5398[DAT_800d1e28].a, DAT_800a5398[DAT_800d1e28].b, c->flag + 1);
	c->ptr = c->buf;
}
