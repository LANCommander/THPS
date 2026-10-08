/* Spool_GetEnvIndex__Fi (0x8007043c) */
#include "names.h"
int DAT_800d1ed0, DAT_800d1ed4;

int Spool_GetEnvIndex(int i) {
	if (i == DAT_800d1ed0)
		return 0;

	if (i == DAT_800d1ed4)
		return 1;

	return -1;
}
