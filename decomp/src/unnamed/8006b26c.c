/* FUN_8006b26c (0x8006b26c) */
extern char DoubleBuffer[];
extern char *pDoubleBuffer;
extern int pPoly;

void FUN_80059018(void);
int FUN_8008c1a0(int a);
void FUN_8008c8dc(char *a);
void FUN_800242cc(void);

void FUN_8006b26c(void) {
	char *a;

	FUN_80059018();
	FUN_8008c1a0(1);
	FUN_8008c8dc(pDoubleBuffer + 16524);

	a = DoubleBuffer;

	if (pDoubleBuffer == a)
		a = a + 32940;

	pDoubleBuffer = a;
	pPoly = *(int *)(a + 32768 + 168) & 0x7fffffff;
	FUN_800242cc();
}
