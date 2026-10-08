/* SetAnglesFromHeading__6CBruce (0x8003a648) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short m[3][3];
	long t[3];
} MATRIX;

typedef struct {
	short vx, vy, vz, pad;
} SVECTOR;

typedef struct {
	char _0[4];
	V pos;
	SVECTOR ang;
	char _18[0x78c - 0x18];
	MATRIX m;
} CBruce;

extern void M3dUtils_AnglesFromMatrix(SVECTOR *, MATRIX *);

void SetAnglesFromHeading(CBruce *b) {
	SVECTOR a;
	int x, y, z;

	b->m.m[0][1] = -b->m.m[0][1];
	b->m.m[1][1] = -b->m.m[1][1];
	b->m.m[2][1] = -b->m.m[2][1];
	M3dUtils_AnglesFromMatrix(&a, &b->m);

	b->m.m[0][1] = -b->m.m[0][1];
	b->m.m[1][1] = -b->m.m[1][1];
	b->m.m[2][1] = -b->m.m[2][1];
	x = a.vx;
	y = a.vy;
	z = a.vz;
	b->ang.vx = x;
	b->ang.vy = y;
	b->ang.vz = z;
}
