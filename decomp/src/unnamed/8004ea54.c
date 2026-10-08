/* FUN_8004ea54 (0x8004ea54) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	V v;
	unsigned char c0, c1, c2, c3;
} E;

typedef struct {
	char p0[0x18];
	V v18;
	char p1[0x44 - 0x24];
	char *vt;
	char p2[0x4c - 0x48];
	int n;
	E *e;
	V v54;
	unsigned char b60, b61, b62;
	char p3;
	int i64;
	char p4[0x6c - 0x68];
	int i6c;
	int i70;
} B;

extern char DAT_800a1308[];

int FUN_800270e0(B *, int);
int Redbook_Rnd__Fi(int);
void SetSemiTransparent__9CPolyLine(B *);

B *FUN_8004ea54(B *p, V *pos, int a2, int a3, unsigned char r, unsigned char g, int a6, int a7) {
	int i;
	unsigned char c = a3;

	FUN_800270e0(p, a6);

	p->vt = DAT_800a1308;
	p->v18 = *pos;
	p->i64 = a2;
	p->i6c = a7;
	p->v54 = *pos;
	p->b60 = c;
	p->b61 = r;
	p->b62 = g;

	for (i = 0; i < p->n; i++) {
		p->e[i].c0 = c;
		p->e[i].c1 = r;
		p->e[i].c2 = g;
		p->e[i].v = *pos;
	}

	p->i70 = Redbook_Rnd__Fi(4096);
	SetSemiTransparent__9CPolyLine(p);
	return p;
}
