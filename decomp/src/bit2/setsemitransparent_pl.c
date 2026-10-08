/* SetSemiTransparent__9CPolyLine (0x80027210) */
#include "names.h"
void CPolyLine_SetSemiTransparent(char *t) {
	int i;

	for (i = 0; i < *(int *)(t + 0x4c); i++)
		(*(char **)(t + 0x50) + i * 16)[15] |= 2;
}
