/* TempRestore__6CBruce (0x8002f118) */
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

void TempRestore(CBruce *b) {
	b->m = b->tm;
	b->pos = b->tpos;
}
