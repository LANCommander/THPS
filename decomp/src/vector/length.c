/* CVector::Length (0x8004d900): GTE SQR of the >>12 components, then SquareRoot0 (0x8008b5dc). */
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>

typedef struct {
	int x, y, z;
} V;

extern long SquareRoot0(long);

int Length(V *v) {
	VECTOR t;

	t.vx = v->x >> 12;
	t.vy = v->y >> 12;
	t.vz = v->z >> 12;
	gte_ldlvl(&t);
	gte_sqr0();
	gte_stlvnl(&t);
	return SquareRoot0(t.vx + t.vy + t.vz);
}
