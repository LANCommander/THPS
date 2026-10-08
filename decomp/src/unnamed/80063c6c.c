/* drawFaded__6Spriteiiiiii (0x80063c6c) */
#include "names.h"
void SlicedImage_draw(int a, int b, int c, int d, int e, int f, int g, int h, int i);

void Sprite_drawFaded(int *p, int a, int b, int c, int d, int e, int f) {
	SlicedImage_draw(p[5], a, b, c, d, e, f, 1, 0);
}
