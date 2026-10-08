/* Matrix2Euler__FP6MATRIXP7SVECTOR (0x80069878) */
#include "names.h"
#include <sys/types.h>
#include <libgte.h>

int FUN_800936d4(int, int);
void FUN_80095cb0(int, MATRIX *);

void Matrix2Euler(MATRIX *mat, SVECTOR *out) {
	MATRIX m = *mat;
	int x, y, z;

	m.m[0][1] = -m.m[0][1];
	m.m[1][1] = -m.m[1][1];
	m.m[2][1] = -m.m[2][1];
	y = FUN_800936d4(m.m[0][2], m.m[2][2]) & 4095;
	FUN_80095cb0(-y, &m);

	x = FUN_800936d4(-m.m[1][2], m.m[2][2]) & 4095;
	FUN_80095cb0(-x, &m);

	z = FUN_800936d4(m.m[1][0], m.m[1][1]) & 4095;
	out->vy = y;
	out->vx = x;
	out->vz = z;
}
