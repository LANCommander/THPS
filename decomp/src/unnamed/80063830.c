/* __6SpritePciii (0x80063830) */
extern char DAT_800a2190[];

int Load8BitBMP__FPcPPcPiT2PUs(char *name, char **a, int *b, int *c, unsigned short *d);
char *__nw__5CItemUi(unsigned n);
char *__11SlicedImagePciiiiiUs(char *p, char *a, int b, int c, int d, int e, int f, int g);
void pack__11SlicedImage(char *p);

char *__6SpritePciii(char *p, char *name, int pk, int mw, int mh) {
	unsigned short pal;
	char *data;
	int w;
	int h;
	char *v;

	*(char **)p = DAT_800a2190;
	Load8BitBMP__FPcPPcPiT2PUs(name, &data, &w, &h, &pal);

	*(int *)(p + 16) = 8;
	*(int *)(p + 4) = w;
	*(int *)(p + 8) = h;

	if (!(mw * 2 < w))
		mw = 0;

	if (!(mh < h))
		mh = 0;

	v = __nw__5CItemUi(52);

	if (v)
		v = __11SlicedImagePciiiiiUs(v, data, w, h, mw, mh, *(int *)(p + 16), pal);

	*(char **)(p + 20) = v;
	data = 0;
	*(int *)(p + 12) = pk;

	if (pk)
		pack__11SlicedImage(v);

	return p;
}
