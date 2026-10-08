/* FUN_8006b26c (0x8006b26c) */
extern char DAT_800a891c[];
extern char *DAT_800d1a48;
extern int DAT_800d1a54;

void FUN_80059018(void);
int FUN_8008c1a0(int a);
void FUN_8008c8dc(char *a);
void FUN_800242cc(void);

void FUN_8006b26c(void) {
	char *a;

	FUN_80059018();
	FUN_8008c1a0(1);
	FUN_8008c8dc(DAT_800d1a48 + 16524);

	a = DAT_800a891c;

	if (DAT_800d1a48 == a)
		a = a + 32940;

	DAT_800d1a48 = a;
	DAT_800d1a54 = *(int *)(a + 32768 + 168) & 0x7fffffff;
	FUN_800242cc();
}
