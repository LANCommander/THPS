/* SetTexture__8CQuadBitPci (0x80028440) */
#include "names.h"
char *Spool_FindAnim(char *);

void CQuadBit_SetTexture(char *t, char *name, int i) {
	char *p = Spool_FindAnim(name);

	*(int *)(t + 0x94) = *(int *)(p + i * 8 + 4);
}
