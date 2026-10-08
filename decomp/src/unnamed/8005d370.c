/* FUN_8005d370 (0x8005d370) */
unsigned DAT_800d1cf8;

void FUN_8005d73c(void);
void FUN_8005d3dc(void);
void FUN_8005da40(void);

void FUN_8005d370(void) {
	switch (DAT_800d1cf8) {
		case 0:
			FUN_8005d73c();
			break;
		case 1:
		case 3:
		case 4:
		case 5:
			FUN_8005d3dc();
			break;
		case 2:
			FUN_8005da40();
			break;
	}
}
