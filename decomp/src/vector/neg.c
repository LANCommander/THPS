typedef struct {
	int x, y, z;
} V;

V *op(V *r, const V *a) {
	int x = -a->x, y = -a->y, z = -a->z;

	r->x = x;
	r->y = y;
	r->z = z;
	return r;
}
