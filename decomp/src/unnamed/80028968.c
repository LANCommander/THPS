/* _._9CChunkBit (0x80028968) */
#include "names.h"
extern char __vt_9CChunkBit[];

char ChunkBitList[8];

int BASEF(char *p, int a);
void CBit_DeleteFrom(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80028968(char *p, int f) {
	*(char **)(p + 68) = __vt_9CChunkBit;
	CBit_DeleteFrom(p, ChunkBitList);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
