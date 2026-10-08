/* BoardOff__6CBruce (0x80041c30) */
#include "names.h"
typedef struct {
	char pad[16];
	unsigned char a, b, c;
	char q[340 - 19];
} T;

typedef struct {
	char pad[404];
	int flags;
	char q[744 - 408];
	int idx;
} P;

extern T Stats[];

void CBruce_BoardOff(P *p) {
	T *base = Stats;
	T *t = &base[p->idx];

	p->flags |= (1 << t->a) | (1 << t->b) | (1 << t->c);
}
