/* Video_Cleanup__Fv (0x80069670) */
#include "names.h"
extern int DAT_800bf318[];
extern int DAT_800bf3d8[];

void Video_Cleanup(void) {
	DAT_800bf318[0] = 0;
	DAT_800bf3d8[0] = 0;
}
