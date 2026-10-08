typedef struct {
	int x, y, z;
} CVector;

CVector *op(CVector *p1, const int *n) {
	p1->x *= *n;
	p1->y *= *n;
	p1->z *= *n;
	return p1;
}
