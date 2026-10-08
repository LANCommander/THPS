/* draw__14VerticalDialog (0x80065394) */
#include "names.h"
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

void Mess_SetTextJustify(int);
void Mess_SetFontScale(unsigned);
void Sprite_draw(int, int, int, int, int, int, int);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText(int, int, char *, int, int, int, int);

void VerticalDialog_draw(VD *t) {
	int i;

	Mess_SetTextJustify(0);
	Mess_SetFontScale(t->f8);

	for (i = 0; i < t->cnt; i++) {
		Sprite_draw(t->e[i].spr, t->e[i].x,
		                    t->e[i].b - ((t->e[i].c >> 1) * t->fc) / t->f8 - 1, 0, -1, -1, -1);

		if (t->e[i].e)
			Mess_SetRGB(64, 64, 64, 0);
		else
			Mess_SetRGB(122, 122, 122, 0);

		Mess_DrawText(t->e[i].a, t->e[i].b - (t->e[i].c >> 1) + t->e[i].d, t->e[i].str, 0, 0, 256,
		             0);
		Mess_SetFontScale(t->f8);
	}
}
