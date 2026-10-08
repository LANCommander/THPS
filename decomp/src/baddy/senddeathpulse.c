/* SendDeathPulse__6CBaddy (0x8003fb68) */
#include "names.h"
extern char **DAT_800d19e8 __attribute__((section(".data")));
void Trig_SendPulse(unsigned short *);

void CBaddy_SendDeathPulse(char *t) {
	if (!t[0x1a1] && *(unsigned short *)(t + 0xe2) != 0xffff) {
		t[0x1a1] = 1;
		Trig_SendPulse((unsigned short *)(DAT_800d19e8[*(unsigned short *)(t + 0xe2)] + 6));
	}
}
