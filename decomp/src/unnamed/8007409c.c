/* Competition_IsOver__Fv (0x8007409c) */
#include "names.h"
extern unsigned char DAT_800c109c[];

int Competition_IsOver(void) {
	return DAT_800c109c[0] >= 3;
}
