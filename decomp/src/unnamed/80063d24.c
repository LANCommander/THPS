/* removeFromMemory__6Sprite (0x80063d24) */
#include "names.h"
void SlicedImage_removeFromMemory(int a);

void Sprite_removeFromMemory(int *p) {
	SlicedImage_removeFromMemory(p[5]);
}
