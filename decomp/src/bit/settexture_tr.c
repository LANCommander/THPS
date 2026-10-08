/* SetTexture__15CTexturedRibbonUi (0x8002e2f0) */
#include "names.h"
int Spool_FindTextureEntry(unsigned);

void CTexturedRibbon_SetTexture(char *t, unsigned a) {
	*(int *)(t + 0x4c) = Spool_FindTextureEntry(a);
}
