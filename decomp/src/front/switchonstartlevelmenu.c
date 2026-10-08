/* Front_SwitchOnStartLevelMenu__Fv (0x8001a5b8) */
#include "names.h"
int DAT_800d13e8;

void CommonSwitchOnMenuCode(void);

void Front_SwitchOnStartLevelMenu(void) {
	DAT_800d13e8 = 33;
	CommonSwitchOnMenuCode();
}
