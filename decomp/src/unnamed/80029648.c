/* Bit_SetSparkSize__FUi (0x80029648) */
#include "names.h"
int DAT_800d18b4;

void Bit_SetSparkSize(int a) {
	DAT_800d18b4 = (a << 16) | a;
}
