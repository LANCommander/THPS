/* Trig_RemoveDualBuffer__Fv (0x8004634c) */
#include "names.h"
void *DAT_800d1a0c;

void Mem_Delete(void *p);

void Trig_RemoveDualBuffer(void) {
	if (DAT_800d1a0c)
		Mem_Delete(DAT_800d1a0c);

	DAT_800d1a0c = 0;
}
