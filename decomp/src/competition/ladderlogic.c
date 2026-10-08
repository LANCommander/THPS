/* Competition_LadderLogic__Fv (0x80074b94) */
#include "names.h"
typedef struct {
	unsigned char a, av, b, bv;
	int pad;
} Ent;

typedef struct {
	char _0[0x14];
	int f14;
	char _18[4];
	unsigned char f1c;
	char _1d[7];
	int f24;
	char _28[4];
	Ent ent[5];
	char _54[8];
	unsigned char type[10];
	char _66[0x70 - 0x66];
	unsigned short tab[30];
	char _ac[0xc0 - 0xac];
	unsigned char c0;
	char _c1[0x128 - 0xc1];
	int n;
} SComp;

extern SComp DAT_800c0fdc;

unsigned short DAT_800d1fc2, DAT_800d1fc4, DAT_800d1fc6, DAT_800d1fc8;

int Redbook_Rnd(int n);

void Competition_LadderLogic(void) {
	unsigned char i, j;
	SComp *c = &DAT_800c0fdc;
	unsigned short s;

	if (c->f14 == 0) {
		c->f24 = 0;

		for (i = 0; i < 10; i++) {
			if (i == c->n)
				continue;

			if (c->type[i] == 0)
				s = DAT_800d1fc2;
			else if (c->type[i] == 1)
				s = DAT_800d1fc4;
			else if (c->type[i] == 2)
				s = DAT_800d1fc6;
			else
				s = DAT_800d1fc8 + Redbook_Rnd(DAT_800d1fc6 - DAT_800d1fc8);

			s -= Redbook_Rnd(18);

			for (j = 0; j < 5; j++) {
				if (i == c->ent[j].a)
					s += c->ent[j].av;

				if (i == c->ent[j].b)
					s -= c->ent[j].bv;
			}

			c->tab[i * 3 + c->c0] = s;
		}

		c->f1c = 0;
	}

	c->f14++;
}
