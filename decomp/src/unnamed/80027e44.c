/* __4CBit (0x80027e44) */
#include "names.h"
extern char __vt_4CBit[];

int BitCount;

char *CBit_ctor(char *p) {
	char *q = p + 60;

	*(char **)(p + 68) = __vt_4CBit;
	p[60] = 1;
	q[1] = 1;
	q[2] = 1;
	BitCount = BitCount + 1;
	return p;
}
