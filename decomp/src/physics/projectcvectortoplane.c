/* ProjectCVectorToPlane__FP7CVectorG7SVECTOR (0x8002fff4) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short vx, vy, vz, pad;
} SVECTOR;

extern int Mips_CVecDotProd__FP7CVectorT0(V *, V *);
extern int Mips_FixMul__Fii(int, int);

void ProjectCVectorToPlane(V *v, SVECTOR n) {
	V t;
	int d;

	t.x = n.vx;
	t.y = n.vy;
	t.z = n.vz;
	d = Mips_CVecDotProd__FP7CVectorT0(v, &t);
	v->x -= Mips_FixMul__Fii(d, n.vx);
	v->y -= Mips_FixMul__Fii(d, n.vy);
	v->z -= Mips_FixMul__Fii(d, n.vz);
}
