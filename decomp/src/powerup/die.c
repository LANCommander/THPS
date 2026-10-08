/* Die__8CPowerUp (0x8001ff44) */
#include "names.h"
int CBody_IsDead(char *);
void CPowerUp_DontDisplay(char *);

void CPowerUp_Die(char *t) {
	if (!CBody_IsDead(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		CPowerUp_DontDisplay(t);
	}
}
