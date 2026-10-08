/* GetFree256Slot__Fv (0x8004ad9c) */
#include "names.h"
extern unsigned char DAT_800d2b10[];

int GetFree256Slot(void) {
	int i = 0;

	while (!DAT_800d2b10[i]) {
		i++;

		if (i >= 75)
			break;
	}

	DAT_800d2b10[i] = 0;
	return i;
}
