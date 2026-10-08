/* removeFromMemory__11SlicedImage (0x80062de8) */
#include "names.h"
void Mem_Delete(int a);

void SlicedImage_removeFromMemory(int *p) {
	if (p[12] == 0) {
		p[12] = 1;
		Mem_Delete(p[5]);
	}
}
