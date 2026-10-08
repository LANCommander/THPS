/* Competition_Init__Fv (0x800740b4) */
typedef struct {
	unsigned char b0, b1, b2, b3, b4, b5, b6, b7;
} CE;

typedef struct {
	char _0[4];
	unsigned char order[10];
	char _e[2];
	int i16, i20, i24;
	char _1c[16];
	CE e[5];
	char _54[8];
	unsigned char w[10];
	unsigned char z[10];
	short x[10][3];
	short y[10];
	unsigned char b192;
	char _c1[0x67];
	int cur;
	int i300;
} Comp;

extern Comp DAT_800c0fdc;
extern int DAT_800d1a20, DAT_800d1114, DAT_800d1e28;

short DAT_800d1fc0, DAT_800d1fc2, DAT_800d1fc4, DAT_800d1fc6, DAT_800d1fc8;

void Redbook_InitialRand__Fi(int);
int Redbook_Rnd__Fi(int);

void Competition_Init__Fv(void) {
	Comp *c = &DAT_800c0fdc;
	unsigned char *p;
	unsigned char *q;
	int i, j, r, cnt, idx, t;
	unsigned char u, k, m;

	c->i16 = 0;
	c->i20 = 0;
	c->i24 = 0;
	c->i300 = 0;
	Redbook_InitialRand__Fi(DAT_800d1a20);

	for (i = 0; i < 10; i++)
		c->order[i] = i;

	t = DAT_800d1114;
	c->cur = t;

	if (t == 10) {
		c->cur = Redbook_Rnd__Fi(10);
		c->order[c->cur] = t;
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

	for (u = 0; u < 5; u++) {
		((unsigned char *)c + (u << 3))[44] = Redbook_Rnd__Fi(10);
		((unsigned char *)c + (u << 3))[46] = Redbook_Rnd__Fi(10);
		((unsigned char *)c + (u << 3))[45] = Redbook_Rnd__Fi(30);
		((unsigned char *)c + (u << 3))[47] = Redbook_Rnd__Fi(30);
	}

	for (k = 0; k < 10; k++) {
		for (m = 0; m < 3; m++)
			c->x[k][m] = 0;

		c->y[k] = 0;
		c->z[k] = k;
	}

	c->b192 = 0;

	for (i = 0; i < 10; i++)
		c->w[i] = 255;

	for (j = 0; j < 10; j++) {
		r = Redbook_Rnd__Fi(10 - j);
		cnt = 0;
		idx = -1;

		while (cnt <= r) {
			idx++;

			if (c->w[idx] == 255)
				cnt++;
		}

		c->w[idx] = j;
	}

	for (i = 0; i < 10; i++)
		if (c->w[i] == 9)
			c->w[i] = c->w[c->cur];

	c->w[c->cur] = 255;
}
