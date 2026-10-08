/* Font_Init__Fv (0x8004c14c) */
#include "names.h"
extern char DAT_800a1270[];
extern char DAT_800d1ae4[];

int DAT_800d1ad8, DAT_800d1adc;

int Spool_FindAnim(char *);

void Font_Init(void) {
	DAT_800d1ad8 = Spool_FindAnim(DAT_800a1270);
	DAT_800d1adc = Spool_FindAnim(DAT_800d1ae4);
}
