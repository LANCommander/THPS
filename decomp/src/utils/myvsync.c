/* MyVSync__Fv (0x80047870) */
int DAT_800d1a20;
int DAT_800d1a24, DAT_800d1a30;

extern int DAT_800d140c, DAT_800d16fc;

int Db_Vblank__Fv(void);
void SFX_ProcessingPerFrame__Fv(void);
void Utils_VblankProcessing__Fv(void);

void MyVSync(void) {
	DAT_800d1a20++;
	Db_Vblank__Fv();
	SFX_ProcessingPerFrame__Fv();

	if (!DAT_800d140c && !DAT_800d16fc)
		DAT_800d1a24++;

	if (DAT_800d1a30)
		Utils_VblankProcessing__Fv();
}
