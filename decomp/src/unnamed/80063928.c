/* __6Spriteiiiiiii (0x80063928) */
#include "names.h"
typedef struct {
	void *vt;
	int w, h, f0c, f10, f14;
} S;

extern char DAT_800a2190[];

int Mem_NewX(int, int, int);
int SlicedImage_ctor(int, int, int, int, int, int, int, int);
void FUN_8008c468(int);
void FUN_8008c774(short *, int);
int __nw__6CClassUi(int);
void SlicedImage_pack(int);
void SlicedImage_removeBlack(int);

S *__6Spriteiiiiiii(S *p, short a1, short a2, int w, int h, int f, int x, int y) {
	short r[4];
	int buf, v;

	p->vt = DAT_800a2190;
	p->f10 = 16;
	p->w = w;
	r[0] = a1;
	r[1] = a2;
	r[2] = w;
	p->h = h;
	r[3] = h;

	if (x >= w)
		x = 0;

	if (y >= h)
		y = 0;

	buf = Mem_NewX(w * h * 2, 1, 1);
	FUN_8008c774(r, buf);
	FUN_8008c468(0);

	v = __nw__6CClassUi(52);

	if (v)
		v = SlicedImage_ctor(v, buf, w, h, x, y, 16, 0);

	p->f14 = v;
	SlicedImage_removeBlack(v);

	p->f0c = f;

	if (f)
		SlicedImage_pack(p->f14);

	return p;
}
