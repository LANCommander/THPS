/* Font_Reset__Fv (0x8004c180) */
#include "names.h"
extern int DAT_800b909c[];
extern char DAT_800b9e9c[];

int DAT_800d1aec, DAT_800d1af0;

void Font_Reset(void) {
	DAT_800d1aec = (int)DAT_800b909c;
	DAT_800b909c[0] = 1;
	DAT_800d1af0 = (int)DAT_800b9e9c;
}
