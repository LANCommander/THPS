/* FUN_800270e0 (0x800270e0) */
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

int __4CBit(struct D *p);

struct E *Mem_NewX__FUiii(int a, int b, int c);

void AttachTo__4CBitPv(struct D *p, int *q);

struct D *FUN_800270e0(struct D *p, int n) {
	int i;

	__4CBit(p);

	p->vt = DAT_8009f670;
	p->e = Mem_NewX__FUiii(n << 4, 0, 1);

	for (i = 0; i < n; i++) {
		p->e[i].w = 0x40ffffff;
		p->e[i].v = DAT_800a824c;
	}

	p->n = n;
	AttachTo__4CBitPv(p, &DAT_800d18f4);
	return p;
}
