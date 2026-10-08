/* Flash_Reset__Fv (0x8001f310) */
int DAT_800d160c;
int DAT_800d1614;
int DAT_800d1610;
char DAT_800d1604;

void Flash_Reset__Fv(void) {
	DAT_800d160c = 0;
	DAT_800d1614 = 0;
	DAT_800d1610 = 0;
	DAT_800d1604 = 0;
}
