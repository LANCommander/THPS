/* FUN_80049474 (0x80049474) */
extern char DAT_800a891c[];

char *DAT_800d1a48;
int DAT_800d1a54;

int FUN_80048c74(void);
void FUN_8008c7d4(char *a, int b);

void FUN_80049474(void) {
	char *a = DAT_800a891c;

	if (DAT_800d1a48 == a)
		a = a + 32940;

	DAT_800d1a48 = a;
	FUN_8008c7d4(DAT_800d1a48 + 132, FUN_80048c74());

	DAT_800d1a54 = *(int *)(DAT_800d1a48 + 32768 + 168) & 0x7fffffff;
}
