/* SetPos__4CBitRC7CVector (0x80027e24) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

void CBit_SetPos(char *t, V *v) {
	*(V *)(t + 0x18) = *v;
}
