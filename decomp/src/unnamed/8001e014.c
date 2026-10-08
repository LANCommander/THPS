/* init__17FallingTextEffect (0x8001e014) */
#include "names.h"
int Redbook_Rnd(int a);

void FallingTextEffect_init(short *p) {
	int i = 0;
	short *q = p;

	for (; i < 32; i++) {
		*q = Redbook_Rnd(30) + 15;
		q++;
	}

	p[32] = 280;
	p[35] = 240;
}
