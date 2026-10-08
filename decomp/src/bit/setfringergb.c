/* SetFringeRGB__5CGlowUiUcUcUc (0x800290a4) */
#include "names.h"
typedef struct {
	int a, b;
} E;

void CGlow_SetFringeRGB(char *t, unsigned a, unsigned char r, unsigned char g,
                                  unsigned char b) {
	unsigned i;
	unsigned c = (0x3a << 24) | (b << 16) | (g << 8) | r;
	E *p = *(E **)(t + 0x4c) + a * *(unsigned *)(t + 0x50);

	for (i = 0; i < *(unsigned *)(t + 0x50); i++)
		p[i].b = c;
}
