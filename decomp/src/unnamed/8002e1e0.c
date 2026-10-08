/* __15CTexturedRibbonii (0x8002e1e0) */
#include "names.h"
extern char __vt_15CTexturedRibbon[];

struct E {
	char pad[16];
	short a, b;
	char pad2[16];
};

struct D {
	char pad[68];
	char *vt;
	char c;
	char pad1[19];
	int q;
	int pad3;
	int n;
	struct E *e;
};

void CTOR(struct D *p);

struct E *Mem_NewX(int a, int b, int c);

struct D *CTexturedRibbon_ctor(struct D *p, int n, int c) {
	int i;

	CTOR(p);

	p->vt = __vt_15CTexturedRibbon;
	p->n = n;
	p->e = Mem_NewX(n * 36, 0, 1);

	for (i = 0; i < p->n; i++) {
		struct E *x = (struct E *)(i * 36 + (int)p->e);

		x->b = 0;
		x->a = 0;
	}

	((char *)p)[72] = c;
	p->q = 8;
	return p;
}
