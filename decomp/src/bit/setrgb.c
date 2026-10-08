/* SetRGB__5CGlowUcUcUc (0x80029048) */
typedef struct {
	int a, b;
} E;

void SetRGB__5CGlowUcUcUc(char *t, unsigned char r, unsigned char g, unsigned char b) {
	unsigned i;
	unsigned c = (b << 16) | (g << 8) | r;

	for (i = 0; i < *(unsigned *)(t + 0x50); i++)
		(*(E **)(t + 0x48))[i].b = c;
}
