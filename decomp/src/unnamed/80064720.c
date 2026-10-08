/* _._12VerticalMenu (0x80064720) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

typedef struct {
	void *obj;
	char text[32];
	int a, b, c, d, e, f, g;
} It;

typedef struct {
	char *vt;
	int sp;
	int fs;
	int w;
	int n;
	int p14;
	int sel;
	It it[12];
	int p31c;
	struct O *q0;
	struct O *q1;
	struct O *q2;
	struct O *q3;
	int f330;
} V;

extern char DAT_800a2158[];
extern char DAT_800a21b0[];

void __dl__6CClassPv(V *);

void FUN_80064720(V *p, int f) {
	int i;

	p->vt = DAT_800a2158;

	if (p->f330 == 0) {
		if (p->q0)
			p->q0->vt->fn((char *)p->q0 + p->q0->vt->off, 3);

		if (p->q1)
			p->q1->vt->fn((char *)p->q1 + p->q1->vt->off, 3);
	}

	if (p->q2)
		p->q2->vt->fn((char *)p->q2 + p->q2->vt->off, 3);

	if (p->q3)
		p->q3->vt->fn((char *)p->q3 + p->q3->vt->off, 3);

	for (i = 0; i < p->n; i++) {
		struct O *o = (struct O *)p->it[i].obj;

		if (o)
			o->vt->fn((char *)o + o->vt->off, 3);
	}

	p->vt = DAT_800a21b0;

	if (f & 1)
		__dl__6CClassPv(p);
}
