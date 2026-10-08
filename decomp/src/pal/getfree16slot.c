/* GetFree16Slot__Fv (0x8004ace8) */
#include "names.h"
extern unsigned char DAT_800d2a10[];

int GetFree16Slot(void) {
	int i = 0;

	while (!DAT_800d2a10[i]) {
		i++;

		if (i >= 256)
			break;
	}

	DAT_800d2a10[i] = 0;
	return i;
}
