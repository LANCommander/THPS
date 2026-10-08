/* FUN_8005c85c (0x8005c85c) */
short DAT_800d1ca0;

void FUN_8005c734(int a);
void FUN_8005c780(void);
int FUN_8008eebc(int a);

void FUN_8005c85c(void) {
	FUN_8005c734(-1);

	while (DAT_800d1ca0 >= 0) {
		FUN_8005c780();
		FUN_8008eebc(0);
	}
}
