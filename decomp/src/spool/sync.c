/* Spool_Sync__Fv (0x8007079c) */
#include "names.h"
extern char DAT_800bf654[][17];
extern int DAT_800d1afc;

int DAT_800d1ef4;

void Spool_Continue(void);
void FileIO_Continue(void);

void Spool_Sync(void) {
	while (DAT_800d1afc || DAT_800bf654[DAT_800d1ef4][13]) {
		Spool_Continue();
		FileIO_Continue();
	}
}
