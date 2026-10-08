/* Shrink__7CFT4Biti (0x80028234) */
#include "names.h"
void CBit_Die(char *);

int CFT4Bit_Shrink(char *t, int kill) {
	if (*(short *)(t + 0x5e) == 0) {
		if (kill)
			CBit_Die(t);

		return 1;
	}

	*(short *)(t + 0x5e) -= *(unsigned short *)(t + 0x4a);

	if (*(short *)(t + 0x5e) < 0)
		*(short *)(t + 0x5e) = 0;

	return 0;
}
