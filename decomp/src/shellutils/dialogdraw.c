/* draw__14VerticalDialog (0x80065394) */
typedef struct {
	int spr;
	char str[0x20];
	int a, b, pad, c, d, e, x;
} E;

typedef struct {
	char pad[8];
	int f8;
	int fc;
	int cnt;
	char pad2[8];
	E e[12];
} VD;

void FUN_8001d250(int);
void Mess_SetFontScale__FUi(unsigned);
void draw__6Spriteiiiiii(int, int, int, int, int, int, int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void FUN_8001e114(int, int, char *, int, int, int, int);

void draw__14VerticalDialog(VD *t) {
	int i;

	FUN_8001d250(0);
	Mess_SetFontScale__FUi(t->f8);

	for (i = 0; i < t->cnt; i++) {
		draw__6Spriteiiiiii(t->e[i].spr, t->e[i].x,
		                    t->e[i].b - ((t->e[i].c >> 1) * t->fc) / t->f8 - 1, 0, -1, -1, -1);

		if (t->e[i].e)
			Mess_SetRGB__FUcUcUci(64, 64, 64, 0);
		else
			Mess_SetRGB__FUcUcUci(122, 122, 122, 0);

		FUN_8001e114(t->e[i].a, t->e[i].b - (t->e[i].c >> 1) + t->e[i].d, t->e[i].str, 0, 0, 256,
		             0);
		Mess_SetFontScale__FUi(t->f8);
	}
}
