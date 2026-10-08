/* FUN_8002a534 (0x8002a534) */
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

extern char DAT_8009f688[];

char DAT_800d18ec[8];

void FUN_80027e44(B *);
void AttachTo__4CBitPv(B *, char *);
int Redbook_Rnd__Fi(int);

B *FUN_8002a534(B *p, V *pos, V *vel, int a3, unsigned char r, unsigned char g, unsigned char b,
                int rx, int ry, int rz) {
	int sx, sy, sz;

	FUN_80027e44(p);

	p->vt = DAT_8009f688;
	AttachTo__4CBitPv(p, DAT_800d18ec);

	sx = rx * 2 + 1;
	sy = ry * 2 + 1;
	sz = rz * 2 + 1;
	p->v18 = *pos;
	p->a48.x = pos->x + ((Redbook_Rnd__Fi(sx) - rx) << 12);
	p->a48.y = pos->y + ((Redbook_Rnd__Fi(sy) - ry) << 12);
	p->a48.z = pos->z + ((Redbook_Rnd__Fi(sz) - rz) << 12);
	p->a54.x = pos->x + ((Redbook_Rnd__Fi(sx) - rx) << 12);
	p->a54.y = pos->y + ((Redbook_Rnd__Fi(sy) - ry) << 12);
	p->a54.z = pos->z + ((Redbook_Rnd__Fi(sz) - rz) << 12);
	p->a60.x = pos->x + ((Redbook_Rnd__Fi(sx) - rx) << 12);
	p->a60.y = pos->y + ((Redbook_Rnd__Fi(sy) - ry) << 12);
	p->a60.z = pos->z + ((Redbook_Rnd__Fi(sz) - rz) << 12);
	p->v24 = *vel;
	p->i6c = a3;
	p->b70 = r >> 2;
	p->b71 = g >> 2;
	p->b72 = b >> 2;
	p->b73 = r >> 2;
	p->b74 = g >> 2;
	p->b75 = b >> 2;
	p->s0a = Redbook_Rnd__Fi(30) + 30;
	p->b76 = 4;
	return p;
}
