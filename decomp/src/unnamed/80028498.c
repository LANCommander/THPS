/* SetSemiTransparent__8CQuadBit (0x80028498) */
#include "names.h"
void CQuadBit_SetSemiTransparent(char *p) {
	*(unsigned *)(p + 144) |= 0x2000000;
}
