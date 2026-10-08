/* CycleAnim__6CSuperiSc (0x80043f24) */
#include "names.h"
typedef struct {
	char p[0x18];
	char *anims;
	char q[0x40 - 0x1c];
} R;

extern R PSXRegion[] __attribute__((section(".data")));

void CSuper_CycleAnim(char *t, int a, signed char c) {
	unsigned char k;

	*(unsigned short *)(t + 0x146) = a;
	k = PSXRegion[(unsigned char)t[0x1b]].anims[*(unsigned short *)(t + 0x146) * 8 + 8];
	t[0x148] = 1;
	t[0x149] = c;
	*(short *)(t + 0x144) = 0;
	*(short *)(t + 0x14c) = 0;
	t[0x14f] = 0;
	t[0x14e] = k;
}
