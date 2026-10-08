/* SetCollisionAngLR__7CCameras (0x80078998) */
#include "names.h"
void CCamera_SetCollisionAngLR(char *p, short v) {
	*(short *)(p + 1372) = v;
}
