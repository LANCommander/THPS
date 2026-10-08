/* FRUVectorsFromRotMatrix__6CBruce (0x8003a5a4) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short m[3][3];
	long t[3];
} MATRIX;

typedef struct {
	char _0[4];
	V pos;
	char _10[0x78c - 0x10];
	MATRIX m;
	MATRIX tm;
	V tpos;
	V F;
	V R;
	V U;
} CBruce;

static __inline__ void Set(V *v, int x, int y, int z) {
	v->x = x;
	v->y = y;
	v->z = z;
}

void FRUVectorsFromRotMatrix(CBruce *b) {
	Set(&b->F, b->m.m[0][2], b->m.m[1][2], b->m.m[2][2]);
	Set(&b->R, b->m.m[0][0], b->m.m[1][0], b->m.m[2][0]);
	Set(&b->U, b->m.m[0][1], b->m.m[1][1], b->m.m[2][1]);
}
