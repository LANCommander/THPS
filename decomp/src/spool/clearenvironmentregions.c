/* Spool_ClearEnvironmentRegions__Fv (0x8006fefc) */
#include "names.h"
int DAT_800d1ed0, DAT_800d1ed4, DAT_800d1ef0;

void ClearRegion(int, int, int);
void Spool_RemoveUnusedTextures(void);

void Spool_ClearEnvironmentRegions(void) {
	ClearRegion(DAT_800d1ed0, 0, 0);
	ClearRegion(DAT_800d1ed4, 0, 0);

	DAT_800d1ed0 = -1;
	DAT_800d1ed4 = -1;
	Spool_RemoveUnusedTextures();

	DAT_800d1ef0 = 0;
}
