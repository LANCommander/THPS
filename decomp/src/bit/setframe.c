/* SetFrame__7CFT4Biti (0x80028140) */
#include "names.h"
void CFT4Bit_SetFrame(char *t, int n) {
	t[0x5a] = n;
	t[0x5b] = 0;
	*(int *)(t + 0x54) = *(int *)(t + 0x50) + (signed char)n * 8;
}
