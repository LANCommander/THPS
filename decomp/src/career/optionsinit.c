/* Options_Init__Fv (0x800105f4) */
#include "names.h"
extern int DAT_800a4118[];
extern char DAT_800d10dc[];
extern char DAT_800d10e4[];
extern int DAT_800d13cc, DAT_800d13d0;

int FUN_8008b900(char *, char *);

void Options_Init(void) {
	int i;

	DAT_800a4118[0] = 12;
	DAT_800d13cc = 16380;
	DAT_800a4118[1] = 6;
	DAT_800d13d0 = 8190;
	DAT_800a4118[97] = 1;
	DAT_800a4118[98] = 1;

	for (i = 0; i < 2; i++) {
		DAT_800a4118[68 + i] = 1;
		DAT_800a4118[70 + i] = 1;
		DAT_800a4118[72 + i * 4] = 0;
		DAT_800a4118[73 + i * 4] = 1;
		DAT_800a4118[74 + i * 4] = 2;
		DAT_800a4118[75 + i * 4] = 3;
	}

	FUN_8008b900((char *)&DAT_800a4118[100], DAT_800d10dc);

	DAT_800a4118[99] = 5;
	FUN_8008b900((char *)&DAT_800a4118[100] - 80, DAT_800d10e4);
}
