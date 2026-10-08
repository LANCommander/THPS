/* SetScale__7CRibboni (0x8002a178) */
#include "names.h"
void CFT4Bit_SetScale(void *, unsigned short);

void CRibbon_SetScale(char *t, int s) {
	int i;

	for (i = 0; i < *(int *)(t + 0x48); i++)
		CFT4Bit_SetScale((*(void ***)(t + 0x5c))[i], s);
}
