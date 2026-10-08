/* SetPos__11CShatterBitRC7CVector (0x80020d0c) */
#include "names.h"
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

short *pNormal;

extern V DAT_800d2574;

void CBit_SetPos(B *, V *);
void CRibbon_SetPos(int, V *);
void CBit_Die(B *);
int CVector_Length(V *);
int Redbook_Rnd(int);
V __mi__FRC7CVectorT0(const V *, const V *);
V __ml__FRCiRC7CVector(const int *, const V *);
V __dv__FRC7CVectorRCi(const V *, const int *);
void __als__7CVectorRCi(V *, const int *);

void CShatterBit_SetPos(B *p, V *a) {
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

	CBit_SetPos(p, a);

	d = __mi__FRC7CVectorT0(a, &DAT_800d2574);
	len = CVector_Length(&d);

	if (len) {
		pr = &r;
		pc = &c;
		n = Redbook_Rnd(48);
		c = __ml__FRCiRC7CVector(&n, &d);
		r = __dv__FRC7CVectorRCi(pc, &len);
		p->v24 = *pr;
	} else {
		CBit_Die(p);
	}

	t = Redbook_Rnd(45);
	q = pNormal;
	p->v24.x += t * q[0];
	p->v24.y += t * q[1];
	p->v24.z += t * q[2];
	p->v24.y -= Redbook_Rnd(175) << 12;

	if (Redbook_Rnd(20) == 0) {
		one = 1;
		__als__7CVectorRCi(&p->v24, &one);
	}

	if (p->v24.y > 0)
		p->v24.y = 0;

	if (p->fc8)
		CRibbon_SetPos(p->fc8, &p->v18);
}
