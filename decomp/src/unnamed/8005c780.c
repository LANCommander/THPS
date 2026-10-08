/* FUN_8005c780 (0x8005c780) */
extern int DAT_800d13cc;

int DAT_800d1cc0;
int DAT_800d1cc4;
short DAT_800d1ca0;
int DAT_800d1ca4;
int DAT_800d1cbc;

void SFX_ModifyVol__FUiii(int a, int b, int c);
void SFX_Stop__FUi(int a);
int FUN_8004b250(int a, int b, int c);

void FUN_8005c780(void) {
	int s = DAT_800d13cc;

	DAT_800d13cc = DAT_800d1cc0;

	if (DAT_800d1cc4) {
		SFX_ModifyVol__FUiii(DAT_800d1ca4, DAT_800d1ca0, DAT_800d1ca0);

		if (DAT_800d1ca0 >= 0) {
			DAT_800d1ca0 -= 256;
		} else {
			SFX_Stop__FUi(DAT_800d1ca4);

			DAT_800d1cc4 = 0;

			if (DAT_800d1cbc != -1)
				DAT_800d1ca4 = FUN_8004b250(DAT_800d1cbc, DAT_800d1ca0, 0);

			DAT_800d1ca0 = 0;
		}
	} else if (DAT_800d1cbc != -1) {
		SFX_ModifyVol__FUiii(DAT_800d1ca4, DAT_800d1ca0, DAT_800d1ca0);

		if (DAT_800d1ca0 < 16384)
			DAT_800d1ca0 += 256;
		else
			DAT_800d1ca0 = 16383;
	}

	DAT_800d13cc = s;
}
