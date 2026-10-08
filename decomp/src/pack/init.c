/* Pack_Init__Fv (0x80049780) */
int DAT_800d1a60, DAT_800d1a64, DAT_800d1a68, DAT_800d1a74, DAT_800d1a78;

void *Pack_NewFree__Fiiii(int, int, int, int);

void Pack_Init__Fv(void) {
	DAT_800d1a68 = 0;
	DAT_800d1a60 = 0;
	DAT_800d1a64 = 0;
	DAT_800d1a74 = 512;
	Pack_NewFree__Fiiii(512, 256, 512, 256);
	Pack_NewFree__Fiiii(512, 0, 512, 256);

	DAT_800d1a78 = 0;
}
