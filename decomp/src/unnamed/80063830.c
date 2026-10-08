/* __6SpritePciii (0x80063830) */
#include "names.h"
extern char __vt_6Sprite[];

int Load8BitBMP(char *name, char **a, int *b, int *c, unsigned short *d);
char *__nw__6CClassUi(unsigned n);
char *SlicedImage_ctor(char *p, char *a, int b, int c, int d, int e, int f, int g);
void SlicedImage_pack(char *p);

char *__6SpritePciii(char *p, char *name, int pk, int mw, int mh) {
	unsigned short pal;
	char *data;
	int w;
	int h;
	char *v;

	*(char **)p = __vt_6Sprite;
	Load8BitBMP(name, &data, &w, &h, &pal);

	*(int *)(p + 16) = 8;
	*(int *)(p + 4) = w;
	*(int *)(p + 8) = h;

	if (!(mw * 2 < w))
		mw = 0;

	if (!(mh < h))
		mh = 0;

	v = __nw__6CClassUi(52);

	if (v)
		v = SlicedImage_ctor(v, data, w, h, mw, mh, *(int *)(p + 16), pal);

	*(char **)(p + 20) = v;
	data = 0;
	*(int *)(p + 12) = pk;

	if (pk)
		SlicedImage_pack(v);

	return p;
}
