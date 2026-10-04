/* FUN_8005c734 (0x8005c734) */
extern int DAT_800a411c[];
int DAT_800d1cbc;
int DAT_800d1cc0;
int DAT_800d1cc4;
void FUN_8005c734(int a)
{
	DAT_800d1cc0 = DAT_800a411c[0] * 16383 / 12;
	if (DAT_800d1cbc != a) {
		DAT_800d1cbc = a;
		DAT_800d1cc4 = 1;
	}
}
