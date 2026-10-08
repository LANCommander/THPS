/* DisplayOutOfBounds__FP6CBruceUsUs (0x8006d704) */
#include "names.h"
/* PANEL.CPP, as C (demo twin; its pString local). Shows the out-of-bounds message (one of four by
   reason) as a text effect at the player's viewport offset until the effect completes. */
typedef struct {
	char p0[0x92c];
	unsigned short f92c;
	char p1[0xad0 - 0x92e];
	int fad0;
	int fad4[1];
} B;

extern int DAT_800a5ec4[], DAT_800a5ec8[], DAT_800a5ecc[], DAT_800a5ed0[];
extern int DAT_800d173c;

void Panel_GetViewportMessOffset(int, short *, short *);
void FUN_8001e07c(int *);
void FUN_8001e0a4(int *, int);
void FUN_8001e0f8(int *, int);
int FUN_8001e108(int *);
void Mess_SetTextJustify(int);
void Mess_DrawPanelText(int, int, char *, int, int, int);

void DisplayOutOfBounds(B *p, int a, int b) {
	short x, y;
	char *s0;

	a &= 0xffff;
	b &= 0xffff;

	if (p->fad0) {
		Panel_GetViewportMessOffset(DAT_800d173c * 2 + p->f92c, &x, &y);

		switch (p->fad0) {
			case 1:
				s0 = (char *)DAT_800a5ec4[0];
				break;
			case 2:
				s0 = (char *)DAT_800a5ec8[0];
				break;
			case 3:
				s0 = (char *)DAT_800a5ecc[0];
				break;
			default:
				s0 = (char *)DAT_800a5ed0[0];
				break;
		}

		FUN_8001e07c(p->fad4);
		FUN_8001e0f8(p->fad4, 256);
		FUN_8001e0a4(p->fad4, 1);
		Mess_SetTextJustify(0);
		Mess_DrawPanelText(a + x, b + y, s0, 0, 0, 256);

		if (FUN_8001e108(p->fad4) == 0)
			p->fad0 = 0;

		FUN_8001e0a4(p->fad4, 0);
	}
}
