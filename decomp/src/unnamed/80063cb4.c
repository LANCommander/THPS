/* pack__6Sprite (0x80063cb4) */
#include "names.h"
int SlicedImage_pack(int a);

void Sprite_pack(int *p) {
	if (p[3] == 0) {
		p[3] = 1;
		SlicedImage_pack(p[5]);
	}
}
