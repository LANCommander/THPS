/* SetRadius__5CGlowi (0x80028f94) */
#include "names.h"
void CGlow_SetRadius(char *t, int r) {
	unsigned i;

	for (i = 0; i < *(unsigned *)(t + 0x50); i++)
		*(int *)(*(char **)(t + 0x48) + i * 8) = r;
}
