/* CalcRGB__FiUiiPUi (0x8002172c) */
#include "names.h"
unsigned char DAT_800d2228, DAT_800d2229, DAT_800d222a;

void CalcRGB(int f, unsigned c, int mode, unsigned *t) {
	unsigned a, b, d;
	int r, g, bl;

	if (f) {
		a = t[c & 255];
		b = t[(c >> 8) & 255];
		d = t[(c >> 16) & 255];
		r = (a & 255) + (b & 255) + (d & 255);
		g = ((a >> 8) & 255) + ((b >> 8) & 255) + ((d >> 8) & 255);
		bl = ((a >> 16) & 255) + ((b >> 16) & 255) + ((d >> 16) & 255);

		if (mode == 4) {
			unsigned e = t[c >> 24];

			r += e & 255;
			g += (e >> 8) & 255;
			bl += (e >> 16) & 255;
			DAT_800d2228 = r / 4;
			DAT_800d2229 = g / 4;
			DAT_800d222a = bl / 4;
		} else {
			DAT_800d2228 = r / 3;
			DAT_800d2229 = g / 3;
			DAT_800d222a = bl / 3;
		}
	} else {
		DAT_800d2228 = c;
		DAT_800d2229 = c >> 8;
		DAT_800d222a = c >> 16;
	}
}
