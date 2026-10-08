/* Die__6CBruce (0x80042778) */
#include "names.h"
int CBody_IsDead(char *);

void CBruce_Die(char *t) {
	if (!CBody_IsDead(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		*(unsigned short *)t |= 0x41;
	}
}
