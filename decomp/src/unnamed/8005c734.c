/* FUN_8005c734 (0x8005c734) */
extern int GPreferences_4[];

int DAT_800d1cbc;
int DAT_800d1cc0;
int DAT_800d1cc4;

void FUN_8005c734(int a) {
	DAT_800d1cc0 = GPreferences_4[0] * 16383 / 12;

	if (DAT_800d1cbc != a) {
		DAT_800d1cbc = a;
		DAT_800d1cc4 = 1;
	}
}
