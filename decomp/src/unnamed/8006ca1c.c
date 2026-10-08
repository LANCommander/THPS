/* FUN_8006ca1c (0x8006ca1c) */
extern int DAT_800d16a4;
extern int DAT_800d17c8;

void Mess_SetRGB__FUcUcUci(unsigned char r, unsigned char g, unsigned char b, int a);

void FUN_8006ca1c(int a) {
	if (DAT_800d16a4 == 8) {
		if (a == DAT_800d17c8)
			Mess_SetRGB__FUcUcUci(80, 80, 128, 0);
		else
			Mess_SetRGB__FUcUcUci(128, 80, 80, 0);
	}
}
