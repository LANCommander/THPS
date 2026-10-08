/* Front_PrintSelect__Fv (0x80017978) */
#include "names.h"
typedef struct {
	int pad[2];
} SAnimFrame;

SAnimFrame *DAT_800d1420;

extern const char *DAT_800a5ef4[];

void Mess_SetTextJustify(int);
void Mess_SetScale(int);
void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText(int, int, const char *, int, int, int, int);
void *Panel_DrawTexturedPoly(SAnimFrame *);
void Panel_SetStretchedScreenCoords(int, int, void *, SAnimFrame *);

void Front_PrintSelect(void) {
	void *p;

	Mess_SetTextJustify(1);
	Mess_SetScale(192);
	Mess_SetRGB(150, 100, 25, 0);
	Mess_DrawText(348, 214, DAT_800a5ef4[0], 0, 0, 256, 0);
	Mess_SetTextJustify(0);

	p = Panel_DrawTexturedPoly(DAT_800d1420);

	if (p)
		Panel_SetStretchedScreenCoords(320, 211, p, DAT_800d1420);
}
