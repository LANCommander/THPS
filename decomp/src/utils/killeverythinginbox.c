/* Utils_KillEverythingInBox__FRC7CVectorT0 (0x800483e8) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

extern void *DAT_800d1998, *DAT_800d19b0, *DAT_800d1618, *DAT_800d19b4;

int Utils_KillObjectsInBox(V *a, V *b, void *list, int f);

int Utils_KillEverythingInBox(V *a, V *b) {
	int n = 0;

	n += Utils_KillObjectsInBox(a, b, DAT_800d1998, 1);
	n += Utils_KillObjectsInBox(a, b, DAT_800d19b0, 1);
	n += Utils_KillObjectsInBox(a, b, DAT_800d1618, 1);
	n += Utils_KillObjectsInBox(a, b, DAT_800d19b4, 0);
	return n;
}
