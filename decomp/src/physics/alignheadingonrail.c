/* AlignHeadingOnRail__6CBruce (0x80033108) */
#include "names.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>

typedef struct {
	int x, y, z;
} V;

void M3dUtils_NormaliseVector(V *);
void CBruce_RotMatrixFromFRUVectors(char *);

void CBruce_AlignHeadingOnRail(char *t) {
	V *a = (V *)(t + 0x7f0);
	V *b = (V *)(t + 0x7d8);

	a->x = 0;
	a->y = -4096;
	a->z = 0;
	gte_ldopv1(b);
	gte_ldopv2(a);
	gte_op12();
	gte_stlvnl((V *)(t + 0x7e4));
	M3dUtils_NormaliseVector((V *)(t + 0x7e4));
	gte_ldopv1((V *)(t + 0x7e4));
	gte_ldopv2(b);
	gte_op12();
	gte_stlvnl(a);
	CBruce_RotMatrixFromFRUVectors(t);
}
