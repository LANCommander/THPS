/* FUN_80025400 (0x80025400) */
extern int DAT_800a7214[];
extern int Xblanks;

int LastXblanks;

void FUN_80025400(void) {
	int i;

	for (i = 0; i < 3; i++)
		DAT_800a7214[i] = 2;

	LastXblanks = Xblanks - 2;
}
