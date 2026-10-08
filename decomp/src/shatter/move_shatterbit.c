/* Move__11CShatterBit (0x80020e8c) */
#include "names.h"
char *__apl__7CVectorRC7CVector(char *, char *);
char *__apl__8CSVectorRC8CSVector(char *, char *);
void CRibbon_SetPos(void *, char *);
void CChunkBit_CalculateWorldCoords(char *);
void CBit_Die(char *);

void CShatterBit_Move(char *t) {
	__apl__7CVectorRC7CVector(t + 0x18, t + 0x24);

	*(int *)(t + 0x28) += 0x5014;
	__apl__8CSVectorRC8CSVector(t + 0x98, t + 0xc0);

	if (*(void **)(t + 0xc8))
		CRibbon_SetPos(*(void **)(t + 0xc8), t + 0x18);

	CChunkBit_CalculateWorldCoords(t);

	if (*(unsigned short *)(t + 10))
		*(unsigned short *)(t + 10) -= 1;
	else
		CBit_Die(t);
}
