/* __amd__7CVectorRC9CFriction (0x8004dbcc) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	unsigned char x, y, z;
} CFriction;

V *op(V *v, const CFriction *f) {
	v->x -= v->x >> f->x;
	v->y -= v->y >> f->y;
	v->z -= v->z >> f->z;
	return v;
}
