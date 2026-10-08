/* __6CLightRC7CVectoriiiiiUcUcUcUcUcUc (0x8001f614) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	char p0[0xa];
	short s0a;
	char p1[0x18 - 0xc];
	V v18;
	char p2[0x43 - 0x24];
	unsigned char b43;
	char *vt;
	int i48;
	int i4c;
	unsigned char c50, c51, c52, c53, c54, c55, b56, p57;
	int i58;
	int i5c;
} B;

extern char DAT_8009f0b0[];

int CNonRenderedBit_ctor(B *);

B *CLight_ctor(B *p, V *pos, int a2, int a3, int a4, int a5, int a6, unsigned char c0,
                unsigned char c1, unsigned char c2, unsigned char c3, unsigned char c4,
                unsigned char c5) {
	CNonRenderedBit_ctor(p);

	p->vt = DAT_8009f0b0;
	p->v18 = *pos;
	p->i5c = a3;
	p->b43 = 2;
	p->s0a = a2;
	p->b56 = 1;
	p->i48 = a4;
	p->i4c = a5;
	p->c50 = c0;
	p->c51 = c1;
	p->c52 = c2;
	p->c53 = c3;
	p->c54 = c4;
	p->c55 = c5;
	p->i58 = a6;
	return p;
}
