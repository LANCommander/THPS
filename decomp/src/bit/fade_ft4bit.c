/* Fade__7CFT4Biti (0x80028290) */
#include "names.h"
typedef struct {
	char _0[0x48];
	short spd;
	char _4a[2];
	unsigned char r, g, b, f;
} Bit;

void CBit_Die(Bit *);

int CFT4Bit_Fade(Bit *t, int kill) {
	unsigned c = *(unsigned *)&t->r;
	int r, g, b;

	if ((c & 0xffffff) == 0) {
		if (kill)
			CBit_Die(t);

		return 1;
	}

	g = (c >> 8) & 255;
	b = (c >> 16) & 255;
	r = t->r;

	if (r < t->spd)
		r = 0;
	else
		r = (r - (unsigned char)t->spd) & 255;

	if (g < t->spd)
		g = 0;
	else
		g = (g - (unsigned char)t->spd) & 255;

	if (b < t->spd)
		b = 0;
	else
		b = (b - (unsigned char)t->spd) & 255;

	*(unsigned *)&t->r = (c & 0xff000000) | (b << 16) | (g << 8) | r;
	return 0;
}
