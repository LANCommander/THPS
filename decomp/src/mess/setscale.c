/* Mess_SetScale__Fi (0x8001d25c) */
unsigned char DAT_800d1602;
short DAT_800d15f8;

extern void Mess_SetFontScale__FUi(unsigned);

void Mess_SetScale(int s) {
	if (DAT_800d1602)
		Mess_SetFontScale__FUi(s);
	else
		DAT_800d15f8 = s;
}
