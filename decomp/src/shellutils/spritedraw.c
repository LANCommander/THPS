/* draw__6Spriteiiiiii (0x80063be4) */
typedef struct {
	int pad[3];
	int stretch;
	int pad2;
	void *img;
} Sprite;

void FUN_80062e20(void *, int, int, int, int, int, int, int, int);
void rotateDraw__11SlicedImageii(void *, int, int);

void Sprite_draw(Sprite *s, int a, int b, int c, int d, int e, int f) {
	if (s->stretch)
		FUN_80062e20(s->img, a, b, c, d, e, f, 0, 0);
	else
		rotateDraw__11SlicedImageii(s->img, a, b);
}
