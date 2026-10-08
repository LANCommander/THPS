/* strKickCD__Fv (0x80023f44) */
int DAT_800d165c;

unsigned char *FUN_800912bc(int, unsigned char *);
int FUN_8008f264(int, unsigned char *, unsigned char *);
int FUN_8008f0ec(int);

void strKickCD(void) {
	unsigned char loc[4];
	unsigned char param[4];

	param[0] = 0x80;
	FUN_800912bc(DAT_800d165c, loc);

	do {
		while (!FUN_8008f264(2, loc, 0))
			;

		while (!FUN_8008f264(14, param, 0))
			;
	} while (!FUN_8008f0ec(480));
}
