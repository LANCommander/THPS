/* FUN_800496b0 (0x800496b0) */
#include "names.h"
typedef struct {
	short a, b, c, d;
} TSPack;

TSPack *DAT_800d1a64;

TSPack *Pack_New(TSPack **);

TSPack *FUN_800496b0(int a, int b, int c, int d) {
	TSPack *p = Pack_New(&DAT_800d1a64);

	p->a = a;
	p->b = b;
	p->c = c;
	p->d = d;
	return p;
}
