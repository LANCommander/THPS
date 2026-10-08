/* Pack_NewFree__Fiiii (0x80049650) */
#include "names.h"
typedef struct TSPack {
	unsigned short x, y, w, h;
	struct TSPack *next;
} TSPack;

TSPack *DAT_800d1a60;

TSPack *Pack_New(TSPack **);

TSPack *Pack_NewFree(int x, int y, int w, int h) {
	TSPack *p = Pack_New(&DAT_800d1a60);

	p->x = x;
	p->y = y;
	p->w = w;
	p->h = h;
	return p;
}
