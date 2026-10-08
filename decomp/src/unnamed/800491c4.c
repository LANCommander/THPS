/* Db_Reset__Fv (0x800491c4) */
#include "names.h"
extern char DAT_800a891c[];

void Db_Reset(void) {
	char *p = DAT_800a891c;
	char *q = p + 32768;
	char *r = p + 65536;

	*(int *)(q + 168) = 0;
	*(int *)(r + 340) = 0;
}
