/* draw__6Spriteiiiiii (0x80063be4) */
#include "names.h"
typedef struct {
	int pad[3];
	int stretch;
	int pad2;
	void *img;
} Sprite;

void SlicedImage_draw(void *, int, int, int, int, int, int, int, int);
void SlicedImage_rotateDraw(void *, int, int);

void Sprite_draw(Sprite *s, int a, int b, int c, int d, int e, int f) {
	if (s->stretch)
		SlicedImage_draw(s->img, a, b, c, d, e, f, 0, 0);
	else
		SlicedImage_rotateDraw(s->img, a, b);
}
