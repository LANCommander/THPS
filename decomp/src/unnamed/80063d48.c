/* __11EraseSpriteiiii (0x80063d48) */
#include "names.h"
extern char DAT_800a2180[];

int Mem_NewX(int a, int b, int c);
void FUN_8008c774(char *p, int a);

char *EraseSprite_ctor(char *p, int a, int b, int c, int d) {
	int n;

	*(short *)(p + 4) = a;
	*(short *)(p + 6) = b;
	*(char **)p = DAT_800a2180;
	*(short *)(p + 8) = c;
	*(short *)(p + 10) = d;
	n = Mem_NewX(c * d * 2, 1, 1);
	*(int *)(p + 12) = n;
	FUN_8008c774(p + 4, n);
	return p;
}
