/* IsDead__C5CBody (0x80043ce8) */
#include "names.h"
int CBody_IsDead(char *p) {
	unsigned x = *(unsigned short *)(p + 82) & 64;

	return x != 0;
}
