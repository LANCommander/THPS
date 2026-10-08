/* SetRadialRGB__5CGlowiUcUcUc (0x80029110) */
typedef struct {
	int a, b;
} E;

void SetRadialRGB__5CGlowiUcUcUc(char *t, int k, unsigned char r, unsigned char g,
                                 unsigned char b) {
	unsigned i;
	unsigned c = (0x3a << 24) | (b << 16) | (g << 8) | r;
	E *p;

	(*(E **)(t + 0x48))[k].b = c;
	p = *(E **)(t + 0x4c) + k;

	for (i = 0; i < *(unsigned *)(t + 0x54); i++) {
		p->b = c;
		p += *(unsigned *)(t + 0x50);
	}
}
