/* CVector::Normalize (0x8004d980). Retail never reloads z: it stores (y/len)/len there (an original bug). */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

extern int CVector_Length(V *);

void Normalize(V *v) {
	int l = CVector_Length(v);

	v->x = v->x / l;
	v->y = v->y / l;
	v->z = v->y / l;
}
