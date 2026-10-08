/* __nw__4CBitUi (0x80027d08) */
#include "names.h"
int UseCacheForBits;

void *Mem_NewX(unsigned int, int, int);

void *__nw__4CBitUi(unsigned int size) {
	int *p;
	unsigned int i, n;

	if (UseCacheForBits)
		p = Mem_NewX(size, 0, 1);
	else
		p = Mem_NewX(size, 0, 1);

	n = (size + 3) >> 2;

	{
		int *q = p;

		for (i = 0; i < n; i++)
			*q++ = 0;
	}

	return p;
}
