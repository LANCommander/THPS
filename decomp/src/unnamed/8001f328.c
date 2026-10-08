/* Flash_FadeFinished__Fv (0x8001f328) */
#include "names.h"
int DAT_800d1614;

int Flash_FadeFinished(void) {
	return DAT_800d1614 == 0;
}
