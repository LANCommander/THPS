/* FUN_800270e0 (0x800270e0) */
#include "names.h"
extern char DAT_8009f670[];
extern int DAT_800d18f4;

struct V {
	int x, y, z;
};

struct E {
	struct V v;
	int w;
};

extern struct V DAT_800a824c;

struct D {
	char pad[68];
	char *vt;
	int q;
	int n;
	struct E *e;
};

int CBit_ctor(struct D *p);

struct E *Mem_NewX(int a, int b, int c);

void CBit_AttachTo(struct D *p, int *q);

struct D *FUN_800270e0(struct D *p, int n) {
	int i;

	CBit_ctor(p);

	p->vt = DAT_8009f670;
	p->e = Mem_NewX(n << 4, 0, 1);

	for (i = 0; i < n; i++) {
		p->e[i].w = 0x40ffffff;
		p->e[i].v = DAT_800a824c;
	}

	p->n = n;
	CBit_AttachTo(p, &DAT_800d18f4);
	return p;
}
