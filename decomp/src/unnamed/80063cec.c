/* unpack__6Sprite (0x80063cec) */
#include "names.h"
void SlicedImage_unpack(int a);

void Sprite_unpack(int *p) {
	if (p[3] != 0) {
		p[3] = 0;
		SlicedImage_unpack(p[5]);
	}
}
