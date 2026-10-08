/* FUN_80065ca4 (0x80065ca4) */
#include "names.h"
extern int DAT_800d1afc;

void FileIO_Continue(int *p);
void Spool_Continue(void);
void FUN_8006582c(int *p);

void FUN_80065ca4(int *p) {
	FileIO_Continue(p);

	if (p[1] == 1)
		Spool_Continue();

	if (p[3] < p[2] && DAT_800d1afc == 0)
		FUN_8006582c(p);
}
