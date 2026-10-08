/* FUN_80014d5c (0x80014d5c) */
int DAT_800d137c, CardLoadFlag, CardStatusMode, DAT_800d139c, DAT_800d13a0, DAT_800d13a4,
    DAT_800d13a8, ev10, ev11, ev12, ev13;

void FUN_8008e944(void);
void FUN_8008e9d4(void);
void FUN_8008ea38(void);
void FUN_8008ea48(int);
int FUN_8008eab8(int, int, int, int);
void FUN_8008eac8(void);
void FUN_8008f0dc(void);

void FUN_80014d5c(void) {
	DAT_800d137c = 1;
	FUN_8008e944();
	FUN_8008e9d4();
	FUN_8008ea38();
	FUN_8008f0dc();

	DAT_800d139c = FUN_8008eab8(0xf4000001, 4, 0x2000, 0);
	DAT_800d13a0 = FUN_8008eab8(0xf4000001, 0x8000, 0x2000, 0);
	DAT_800d13a4 = FUN_8008eab8(0xf4000001, 0x100, 0x2000, 0);
	DAT_800d13a8 = FUN_8008eab8(0xf4000001, 0x2000, 0x2000, 0);
	ev10 = FUN_8008eab8(0xf0000011, 4, 0x2000, 0);
	ev11 = FUN_8008eab8(0xf0000011, 0x8000, 0x2000, 0);
	ev12 = FUN_8008eab8(0xf0000011, 0x100, 0x2000, 0);
	ev13 = FUN_8008eab8(0xf0000011, 0x2000, 0x2000, 0);
	FUN_8008eac8();
	FUN_8008ea48(DAT_800d139c);
	FUN_8008ea48(DAT_800d13a0);
	FUN_8008ea48(DAT_800d13a4);
	FUN_8008ea48(DAT_800d13a8);
	FUN_8008ea48(ev10);
	FUN_8008ea48(ev11);
	FUN_8008ea48(ev12);
	FUN_8008ea48(ev13);

	CardStatusMode = 0;
	CardLoadFlag = 0;
}
