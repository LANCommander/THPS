/* FUN_800117b4 (0x800117b4) */
int DAT_800d10fc;
int DAT_800d1100;
int DAT_800d1148;

extern char DAT_800c0a48[];
extern char DAT_800a42d0[];
extern char DAT_800a42e8[];
extern char DAT_800a42dc[];

void FUN_8008e904(char *a, char *b);

void FUN_800117b4(void) {
	DAT_800d10fc = 0;
	DAT_800d1100 = 0;
	DAT_800c0a48[161] = 0;
	DAT_800c0a48[177] = 0;
	DAT_800c0a48[525] = 0;
	DAT_800c0a48[541] = 0;

	if (DAT_800d1148 == 0)
		FUN_8008e904(DAT_800a42d0, DAT_800a42e8);
	else
		FUN_8008e904(DAT_800a42d0, DAT_800a42dc);
}
