/* SetSemiTransparent__7CFT4Bit (0x800280b0) */
#include "names.h"
void CFT4Bit_SetSemiTransparent(char *p) {
	*(unsigned *)(p + 76) |= 0x2000000;
}
