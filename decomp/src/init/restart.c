/* Init_Restart__F13EPackInitTypei (0x80071e88) */
extern int DAT_800d1150, DAT_800d114c, DAT_800d13d4;

void Init_Cleanup__Fi(int);
void Init_ResetMemory__Fi(int);
void Db_Reset__Fv(void);
void Spool_Init__Fv(void);
void Flash_Reset__Fv(void);
void Pack_Init640x480__Fv(void);
void Pack_Init__Fv(void);
void SFX_InitAtStart__Fv(void);
void Pal_Init__Fv(void);
void Font_Reset__Fv(void);
void Pad_LockAnalog__Fv(void);

void Init_Restart(int type, int b) {
	DAT_800d1150 = 0;
	DAT_800d114c = 0;
	Init_Cleanup__Fi(0);
	Init_ResetMemory__Fi(b);
	Db_Reset__Fv();
	Spool_Init__Fv();

	DAT_800d13d4 = 20;
	Flash_Reset__Fv();

	if (type == 1)
		Pack_Init640x480__Fv();
	else
		Pack_Init__Fv();

	SFX_InitAtStart__Fv();
	Pal_Init__Fv();
	Font_Reset__Fv();
	Pad_LockAnalog__Fv();
}
