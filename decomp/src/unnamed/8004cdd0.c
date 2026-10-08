/* FileIO_Sync__Fv (0x8004cdd0) */
#include "names.h"
int DAT_800d1b14;
int DAT_800d1afc;

void FileIO_Continue(void);
void FUN_8005dcc4(void);

void FileIO_Sync(void) {
	if (DAT_800d1b14) {
		DAT_800d1afc = 0;
		DAT_800d1b14 = 0;
		return;
	}

	while (DAT_800d1afc) {
		FileIO_Continue();
		FUN_8005dcc4();
	}

	FileIO_Continue();
}
