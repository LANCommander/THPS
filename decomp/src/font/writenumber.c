/* WriteNumber__Fi (0x8004c070) */
#include "names.h"
char *DAT_800d1af0;

void WriteNumber(int n) {
	int started = 0;
	int d, q;

	if (n < 0) {
		n = -n;
		*DAT_800d1af0++ = '-';
	}

	for (d = 1000000000; d > 0; d /= 10) {
		if (n >= d) {
			q = n / d;
			started = 1;
			*DAT_800d1af0++ = q + '0';
			n -= q * d;
		} else if (started || d == 1) {
			*DAT_800d1af0++ = '0';
		}
	}

	*DAT_800d1af0++ = 0;
}
