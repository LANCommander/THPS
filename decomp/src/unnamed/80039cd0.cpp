/* FUN_80039cd0 (0x80039cd0) */
/* C++: CC1=D:/Tools/psyq4.5/CC1PLPSX.EXE match_sym.mjs ... "-O2 -fno-exceptions" */
struct CVector {
	int x, y, z;
	int operator!=(const CVector &);
};

typedef CVector V;

typedef struct {
	short vx, vy, vz, pad;
} SVECTOR;

typedef struct {
	short m[3][3];
	long t[3];
} MATRIX;

extern "C" int FUN_80093240(SVECTOR *, MATRIX *);
extern "C" void FUN_80093130(void *, MATRIX *);
extern "C" void FUN_800930c0(void *, MATRIX *);
extern "C" void FRUVectorsFromRotMatrix__6CBruce(void *);
extern "C" int FUN_800720ec(V *, V *);
extern "C" long FUN_8008b5dc(long);
extern CVector operator*(const CVector &, const int &);
extern CVector operator/(const CVector &, const int &);

extern "C" char DAT_800a824c[];

void FUN_80039cd0(char *t, int a, int c, int b) {
	MATRIX m;
	SVECTOR ang;
	MATRIX m3;
	MATRIX m2;
	V tmp;
	V r;
	int l0, l1;
	V *s1;

	if (a) {
		if (*(int *)(t + 856) == 0) {
			if (!((*(V *)(t + 2068)).operator!=(*(V *)DAT_800a824c))) {
				ang.vz = 0;
				ang.vx = 0;
				ang.vy = a & 4095;
				FUN_80093240(&ang, &m);
				FUN_80093130(t + 1932, &m);
				FRUVectorsFromRotMatrix__6CBruce(t);

				if (c) {
					s1 = (V *)(t + 108);
					l0 = FUN_8008b5dc(FUN_800720ec(s1, s1)) << 6;
					FUN_800930c0(t + 1900, &m2);

					ang.vz = 0;
					ang.vx = 0;
					ang.vy = (a - b) & 4095;
					FUN_80093240(&ang, &m);
					FUN_80093130(&m2, &m);

					m3 = *(MATRIX *)(t + 1900);
					FUN_80093130(&m3, &m2);

					tmp.x = m3.m[0][0];
					tmp.y = m3.m[0][1];
					tmp.z = m3.m[0][2];
					r.x = FUN_800720ec(&tmp, s1);
					tmp.x = m3.m[1][0];
					tmp.y = m3.m[1][1];
					tmp.z = m3.m[1][2];
					r.y = FUN_800720ec(&tmp, s1);
					tmp.x = m3.m[2][0];
					tmp.y = m3.m[2][1];
					tmp.z = m3.m[2][2];
					r.z = FUN_800720ec(&tmp, s1);
					*s1 = r;
					l1 = FUN_8008b5dc(FUN_800720ec(s1, s1)) << 6;
					l0 >>= 8;
					l1 >>= 8;
					*s1 = (*s1 * l0) / l1;
				}
			}
		}
	}
}
