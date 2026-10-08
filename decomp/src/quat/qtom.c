/* QToM__FRC5CQuatR6MATRIX (0x800775e8) */
typedef struct {
	int _0, x, y, z, w;
} CQuat;

typedef struct {
	short m[3][3];
	int t[3];
} MATRIX;

void QToM(const CQuat *q, MATRIX *m) {
	int wx = (q->w * q->x) >> 11;
	int wy = (q->w * q->y) >> 11;
	int wz = (q->w * q->z) >> 11;
	int xx = (q->x * q->x) >> 11;
	int xy = (q->x * q->y) >> 11;
	int yy = (q->y * q->y) >> 11;
	int zz = (q->z * q->z) >> 11;
	int xz = (q->x * q->z) >> 11;
	int yz = (q->y * q->z) >> 11;

	m->t[0] = 0;
	m->t[1] = 0;
	m->t[2] = 0;
	m->m[0][0] = 4096 - (yy + zz);
	m->m[0][1] = xy + wz;
	m->m[1][0] = xy - wz;
	m->m[1][1] = 4096 - (xx + zz);
	m->m[2][2] = 4096 - (xx + yy);
	m->m[0][2] = xz - wy;
	m->m[2][0] = xz + wy;
	m->m[1][2] = yz + wx;
	m->m[2][1] = yz - wx;
}
