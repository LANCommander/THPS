/* Panel_addPrim__FPv (0x8006c478) */
#include "names.h"
typedef struct {
	char pad[0x84];
	unsigned long ot;
} O;

extern O *DAT_800d1a48;

int DAT_800d1ecc;

void Panel_addPrim(unsigned long *p) {
	O *o = DAT_800d1a48;

	*p = (*p & 0xff000000) | (o->ot & 0x00ffffff);
	o->ot = (o->ot & 0xff000000) | ((unsigned long)p & 0x00ffffff);
	DAT_800d1ecc = 1;
}
