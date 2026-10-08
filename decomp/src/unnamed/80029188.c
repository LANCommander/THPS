/* __11CWobblyGlowRC7CVectoriiiUcUcUcUcUcUc (0x80029188) */
#include "names.h"
extern char __vt_11CWobblyGlow[];

void __5CGlowRC7CVectoriiUcUcUcUcUcUc(char *p, int a, int b, int c, unsigned char b1, unsigned char b2,
                  unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6);
int Redbook_Rnd(int a);

char *CWobblyGlow_ctor(char *p, int a, int s, int c, int e, unsigned char b1, unsigned char b2,
                   unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6) {
	unsigned i;

	__5CGlowRC7CVectoriiUcUcUcUcUcUc(p, a, s, c, b1, b2, b3, b4, b5, b6);

	*(char **)(p + 68) = __vt_11CWobblyGlow;
	*(int *)(p + 172) = s;
	*(int *)(p + 168) = (s * e) / 256;

	for (i = 0; i < *(unsigned *)(p + 80); i++) {
		*(int *)(p + 136 + i * 4) = Redbook_Rnd(4096);
		*(int *)(p + 104 + i * 4) = Redbook_Rnd(50) + 50;
	}

	return p;
}
