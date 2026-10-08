/* DontDisplay__8CPowerUp (0x8001fe7c) */
#include "names.h"
void CPowerUp_DontDisplay(char *p) {
	char *vt;

	void (*fn)(char *);
	*(unsigned short *)p |= 65;
	vt = *(char **)(p + 72);
	fn = *(void (**)(char *))(vt + 60);
	fn(p + *(short *)(vt + 56));
}
