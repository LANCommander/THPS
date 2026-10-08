/* reset__9PadBuffer (0x800642c0) */
#include "names.h"
void PadBuffer_reset(int *p) {
	p[1] = 0;
	p[2] = 0;
	p[68] = 0;
	p[67] = 0;
}
