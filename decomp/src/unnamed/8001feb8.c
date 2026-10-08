/* SetGravity__8CPowerUpii (0x8001feb8) */
#include "names.h"
void CPowerUp_SetGravity(char *p, int a, char b) {
	*(int *)(p + 124) = a;
	*(char *)(p + 134) = b;
}
