/* Bit_SetSparkTrajectoryCone__FRC8CSVector (0x8002952c) */
#include "names.h"
struct S6 {
	short x, y, z;
};

struct S6 DAT_800d18ac[1];

void Bit_SetSparkTrajectoryCone(struct S6 *p) {
	DAT_800d18ac[0] = *p;
}
