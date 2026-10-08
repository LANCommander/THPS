/* InitItem__5CItemPc (0x800435b8) */
#include "names.h"
int Spool_FindRegion(char *);

void CItem_InitItem(char *t, char *name) {
	t[0x1b] = Spool_FindRegion(name);
	*(short *)(t + 0x16) = 0;
}
