/* SetPos__11CShatterBitRC7CVector (0x80020d0c) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	char p0[0x18];
	V v18;
	V v24;
	char p1[0xc8 - 0x30];
	int fc8;
} B;

short *DAT_800d1624;

extern V DAT_800d2574;

void SetPos__4CBitRC7CVector(B *, V *);
void SetPos__7CRibbonR7CVector(int, V *);
void Die__4CBit(B *);
int Length__C7CVector(V *);
int Redbook_Rnd__Fi(int);
V __mi__FRC7CVectorT0(const V *, const V *);
V __ml__FRCiRC7CVector(const int *, const V *);
V __dv__FRC7CVectorRCi(const V *, const int *);
void __als__7CVectorRCi(V *, const int *);

void SetPos__11CShatterBitRC7CVector(B *p, V *a) {
	V d;
	int pd;
	V r;
	int pr_;
	V c;
	int pc_;
	int n, len, one, t;
	V *pr;
	V *pc;
	short *q;

	SetPos__4CBitRC7CVector(p, a);

	d = __mi__FRC7CVectorT0(a, &DAT_800d2574);
	len = Length__C7CVector(&d);

	if (len) {
		pr = &r;
		pc = &c;
		n = Redbook_Rnd__Fi(48);
		c = __ml__FRCiRC7CVector(&n, &d);
		r = __dv__FRC7CVectorRCi(pc, &len);
		p->v24 = *pr;
	} else {
		Die__4CBit(p);
	}

	t = Redbook_Rnd__Fi(45);
	q = DAT_800d1624;
	p->v24.x += t * q[0];
	p->v24.y += t * q[1];
	p->v24.z += t * q[2];
	p->v24.y -= Redbook_Rnd__Fi(175) << 12;

	if (Redbook_Rnd__Fi(20) == 0) {
		one = 1;
		__als__7CVectorRCi(&p->v24, &one);
	}

	if (p->v24.y > 0)
		p->v24.y = 0;

	if (p->fc8)
		SetPos__7CRibbonR7CVector(p->fc8, &p->v18);
}
