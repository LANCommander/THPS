/* HasSoundCmd__Fv (0x80068df8) */
#include "names.h"
int DAT_800d1df4;
int DAT_800d1df8;

int HasSoundCmd(void) {
	return DAT_800d1df4 != DAT_800d1df8;
}
