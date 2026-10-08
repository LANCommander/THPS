/* Move__11CShatterBit (0x80020e8c) */
char *__apl__7CVectorRC7CVector(char *, char *);
char *__apl__8CSVectorRC8CSVector(char *, char *);
void SetPos__7CRibbonR7CVector(void *, char *);
void CalculateWorldCoords__9CChunkBit(char *);
void FUN_80027e18(char *);

void Move__11CShatterBit(char *t) {
	__apl__7CVectorRC7CVector(t + 0x18, t + 0x24);

	*(int *)(t + 0x28) += 0x5014;
	__apl__8CSVectorRC8CSVector(t + 0x98, t + 0xc0);

	if (*(void **)(t + 0xc8))
		SetPos__7CRibbonR7CVector(*(void **)(t + 0xc8), t + 0x18);

	CalculateWorldCoords__9CChunkBit(t);

	if (*(unsigned short *)(t + 10))
		*(unsigned short *)(t + 10) -= 1;
	else
		FUN_80027e18(t);
}
