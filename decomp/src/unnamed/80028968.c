/* _._9CChunkBit (0x80028968) */
#include "names.h"
extern char DAT_8009f818[];

char DAT_800d18e4[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80028968(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f818;
	CBit_DeleteFrom(p, DAT_800d18e4);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
