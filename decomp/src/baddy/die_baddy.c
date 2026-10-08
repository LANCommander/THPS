/* Die__6CBaddy (0x8003fb1c) */
#include "names.h"
int CBody_IsDead(char *);
void CBaddy_SendDeathPulse(char *);

void CBaddy_Die(char *t) {
	if (!CBody_IsDead(t)) {
		CBaddy_SendDeathPulse(t);

		*(unsigned short *)(t + 0x52) |= 0x40;
		*(unsigned short *)t |= 0x41;
	}
}
