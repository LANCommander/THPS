/* handleLidOpen__Fv (0x80023c48) */
int FUN_8008f4d4(int, unsigned char *, unsigned char *);

void handleLidOpen(void) {
	unsigned char res[8];

	do
		FUN_8008f4d4(1, 0, res);

	while (res[0] & 0x10);

	FUN_8008f4d4(19, 0, 0);

	while (!(res[0] & 2))
		FUN_8008f4d4(1, 0, res);
}
