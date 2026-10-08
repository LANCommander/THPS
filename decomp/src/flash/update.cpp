/* Flash_Update__Fv (0x8001f3f4) */
int DAT_800d1610;
int DAT_800d1614;
int DAT_800d160c;
char DAT_800d1604;
int DAT_800d2208;
int DAT_800d220c;
int DAT_800d2210;
int DAT_800d2214;
int DAT_800d2218;
int DAT_800d221c;

void Flash_Update(void) {
	if (DAT_800d1610) {
		if (DAT_800d1614) {
			DAT_800d1614--;

			if (DAT_800d1614 == 0) {
				DAT_800d2208 = DAT_800d220c = DAT_800d2210 = 0xff0000;
			} else {
				DAT_800d2208 += DAT_800d2214;
				DAT_800d220c += DAT_800d2214;
				DAT_800d2210 += DAT_800d2214;
			}
		}
	} else if (DAT_800d160c) {
		DAT_800d160c--;

		if (DAT_800d160c == 0) {
			DAT_800d1604 = 0;
		} else {
			DAT_800d2208 -= DAT_800d2214;
			DAT_800d220c -= DAT_800d2218;
			DAT_800d2210 -= DAT_800d221c;
		}
	}
}
