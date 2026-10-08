/* Free256Slot__FUs (0x8004adec) */
#include "names.h"
extern unsigned char DAT_800d2b10[];

int DAT_800d1a8c, DAT_800d1a90;

unsigned short FUN_8008f70c(int, int);

void Free256Slot(unsigned short clut) {
	int i;

	for (i = 0; i < 75; i++)
		if (FUN_8008f70c(DAT_800d1a8c, DAT_800d1a90 + i) == clut)
			break;

	DAT_800d2b10[i] = 1;
}
