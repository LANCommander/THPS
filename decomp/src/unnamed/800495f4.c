/* Pack_KillSlot__FP6TSPack (0x800495f4) */
#include "names.h"
int DAT_800d1a68;

void Mem_Delete(void);

void Pack_KillSlot(void) {
	Mem_Delete();

	DAT_800d1a68 = DAT_800d1a68 - 1;
}
