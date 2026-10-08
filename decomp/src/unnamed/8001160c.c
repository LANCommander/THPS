/* Front_InitMemCardMenus__Fi13EMemCardState13EPausedStatus (0x8001160c) */
#include "names.h"
int DAT_800d21e0;
int DAT_800d1118;
int DAT_800d1128;
int DAT_800d111c;
int DAT_800d1124;

void Front_InitMemCardMenus(int a, int b, int c) {
	DAT_800d21e0 = c;
	DAT_800d1118 = 0;
	DAT_800d1128 = a;
	DAT_800d111c = b;
	DAT_800d1124 = 0;
}
