/* SetTint__7CRibbonUcUcUc (0x8002a0e8) */
#include "names.h"
void CFT4Bit_SetTint(void *, unsigned char, unsigned char, unsigned char);

void CRibbon_SetTint(char *t, unsigned char r, unsigned char g, unsigned char b) {
	int i;

	for (i = 0; i < *(int *)(t + 0x48); i++)
		CFT4Bit_SetTint((*(void ***)(t + 0x5c))[i], r, g, b);
}
