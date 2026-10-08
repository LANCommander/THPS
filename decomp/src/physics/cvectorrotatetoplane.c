/* CVectorRotateToPlane__FP7CVectorP7SVECTORT0 (0x80030090) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short vx, vy, vz, pad;
} SVECTOR;

extern int Mips_CVecDotProd__FP7CVectorT0(V *, V *);
extern long FUN_8008b5dc(long);
extern void ProjectCVectorToPlane__FP7CVectorG7SVECTOR(V *, SVECTOR);
extern V __ml__FRC7CVectorRCi(const V *, const int *);
extern V __dv__FRC7CVectorRCi(const V *, const int *);

void CVectorRotateToPlane(V *v, SVECTOR *n, V *out) {
	int l1, l0;
	V a;
	V b;
	SVECTOR nn;

	l0 = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(v, v)) << 6;
	*out = *v;
	nn = *n;
	ProjectCVectorToPlane__FP7CVectorG7SVECTOR(out, nn);

	l1 = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(out, out)) << 6;
	l1 >>= 8;
	l0 >>= 8;
	a = __ml__FRC7CVectorRCi(out, &l0);
	b = __dv__FRC7CVectorRCi(&a, &l1);
	*out = b;
}
