/* CalculateWorldCoords__9CChunkBit (0x80028b6c) */
#include "names.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>

void FUN_8008b3d4(char *, char *);
void FUN_8008f76c(char *);
void FUN_80089f54(char *);

void CChunkBit_CalculateWorldCoords(char *t) {
	char m[0x20];

	FUN_8008b3d4(t + 0x98, m);
	FUN_8008f76c(m);
	FUN_80089f54(t + 0x18);
	gte_ldv0(t + 0x48);
	gte_rtv0tr();
	gte_stlvnl(t + 0x68);
	gte_ldv0(t + 0x50);
	gte_rtv0tr();
	gte_stlvnl(t + 0x74);
	gte_ldv0(t + 0x58);
	gte_rtv0tr();
	gte_stlvnl(t + 0x80);
	gte_ldv0(t + 0x60);
	gte_rtv0tr();
	gte_stlvnl(t + 0x8c);
}
