/* __nw__6CClassUi (0x800241dc) */
#include "names.h"
void *Mem_NewX(unsigned, int, int);

void *__nw__6CClassUi(unsigned size) {
	void *p = Mem_NewX(size, 0, 1);
	int *q = p;
	unsigned i;

	for (i = 0; i < (size + 3) >> 2; i++)
		*q++ = 0;

	return p;
}
