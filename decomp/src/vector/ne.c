typedef struct {
	int x, y, z;
} V;

int op(const V *a, const V *b) {
	return a->x != b->x || a->y != b->y || a->z != b->z;
}
