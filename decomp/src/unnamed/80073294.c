/* DontDisplay__5CTape (0x80073294) */
#include "names.h"
void CTape_DontDisplay(char *p) {
	char *vt;

	void (*fn)(char *);
	*(unsigned short *)p |= 65;
	vt = *(char **)(p + 72);
	fn = *(void (**)(char *))(vt + 60);
	fn(p + *(short *)(vt + 56));
}
