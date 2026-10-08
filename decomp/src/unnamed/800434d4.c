/* __nw__5CItemUi (0x800434d4) */
#include "names.h"
int *Mem_NewX(unsigned n, int a, int b);

int *__nw__5CItemUi(unsigned n) {
	int *r = Mem_NewX(n, 0, 1);
	int *q = r;
	unsigned c = (n + 3) >> 2;
	unsigned i;

	for (i = 0; i < c; i++)
		*q++ = 0;

	return r;
}
