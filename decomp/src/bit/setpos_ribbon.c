/* SetPos__7CRibbonR7CVector (0x8002a1e8) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct Item {
	char _0[0x60];
	V a;
	V b;
} Item;

typedef struct {
	char _0[0x48];
	int n;
	int step;
	int count;
	int idx;
	V *pts;
	Item **items;
} Ribbon;

void CRibbon_SetPos(Ribbon *t, V *p) {
	int i, j;

	t->idx++;

	if (t->idx == t->count)
		t->idx = 0;

	t->pts[t->idx] = *p;
	j = t->idx;

	for (i = t->n - 1; i >= 0; i--) {
		t->items[i]->b = t->pts[j];
		j -= t->step;

		if (j < 0)
			j += t->count;

		t->items[i]->a = t->pts[j];
	}
}
