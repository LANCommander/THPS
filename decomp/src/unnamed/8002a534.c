/* __9CGlassBitRC7CVectorT1iUcUcUciii (0x8002a534) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	char p0[0xa];
	short s0a;
	char p1[0x18 - 0xc];
	V v18;
	V v24;
	char p2[0x44 - 0x30];
	char *vt;
	V a48;
	V a54;
	V a60;
	int i6c;
	unsigned char b70, b71, b72, b73, b74, b75, b76;
} B;

extern char __vt_9CGlassBit[];

char GlassList[8];

void CBit_ctor(B *);
void CBit_AttachTo(B *, char *);
int Redbook_Rnd(int);

B *CGlassBit_ctor(B *p, V *pos, V *vel, int a3, unsigned char r, unsigned char g, unsigned char b,
                int rx, int ry, int rz) {
	int sx, sy, sz;

	CBit_ctor(p);

	p->vt = __vt_9CGlassBit;
	CBit_AttachTo(p, GlassList);

	sx = rx * 2 + 1;
	sy = ry * 2 + 1;
	sz = rz * 2 + 1;
	p->v18 = *pos;
	p->a48.x = pos->x + ((Redbook_Rnd(sx) - rx) << 12);
	p->a48.y = pos->y + ((Redbook_Rnd(sy) - ry) << 12);
	p->a48.z = pos->z + ((Redbook_Rnd(sz) - rz) << 12);
	p->a54.x = pos->x + ((Redbook_Rnd(sx) - rx) << 12);
	p->a54.y = pos->y + ((Redbook_Rnd(sy) - ry) << 12);
	p->a54.z = pos->z + ((Redbook_Rnd(sz) - rz) << 12);
	p->a60.x = pos->x + ((Redbook_Rnd(sx) - rx) << 12);
	p->a60.y = pos->y + ((Redbook_Rnd(sy) - ry) << 12);
	p->a60.z = pos->z + ((Redbook_Rnd(sz) - rz) << 12);
	p->v24 = *vel;
	p->i6c = a3;
	p->b70 = r >> 2;
	p->b71 = g >> 2;
	p->b72 = b >> 2;
	p->b73 = r >> 2;
	p->b74 = g >> 2;
	p->b75 = b >> 2;
	p->s0a = Redbook_Rnd(30) + 30;
	p->b76 = 4;
	return p;
}
