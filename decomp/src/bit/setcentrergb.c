/* SetCentreRGB__5CGlowUcUcUc (0x8002901c) */
#include "names.h"
void CGlow_SetCentreRGB(char *t, unsigned char r, unsigned char g, unsigned char b) {
	*(unsigned *)(t + 0x58) = (0x32 << 24) | (b << 16) | (g << 8) | r;
}
