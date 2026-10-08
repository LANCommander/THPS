/* FUN_80049474 (0x80049474) */
extern char DoubleBuffer[];

char *pDoubleBuffer;
int pPoly;

int FUN_80048c74(void);
void FUN_8008c7d4(char *a, int b);

void FUN_80049474(void) {
	char *a = DoubleBuffer;

	if (pDoubleBuffer == a)
		a = a + 32940;

	pDoubleBuffer = a;
	FUN_8008c7d4(pDoubleBuffer + 132, FUN_80048c74());

	pPoly = *(int *)(pDoubleBuffer + 32768 + 168) & 0x7fffffff;
}
