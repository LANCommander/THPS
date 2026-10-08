/* Die__5CBody (0x80043cac) */
#include "names.h"
int CBody_IsDead(char *);

void CBody_Die(char *t) {
	if (!CBody_IsDead(t))
		*(unsigned short *)(t + 0x52) |= 0x40;
}
