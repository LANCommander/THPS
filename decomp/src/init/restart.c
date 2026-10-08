/* Init_Restart__F13EPackInitTypei (0x80071e88) */
extern int DAT_800d1150, DAT_800d114c, DAT_800d13d4;

void FUN_80071c24(int);
void FUN_80071e40(int);
void FUN_800491c4(void);
void FUN_8006ec14(void);
void Flash_Reset__Fv(void);
void Pack_Init640x480__Fv(void);
void Pack_Init__Fv(void);
void FUN_8004b038(void);
void FUN_8004aa6c(void);
void Font_Reset__Fv(void);
void Pad_LockAnalog__Fv(void);

void Init_Restart(int type, int b) {
	DAT_800d1150 = 0;
	DAT_800d114c = 0;
	FUN_80071c24(0);
	FUN_80071e40(b);
	FUN_800491c4();
	FUN_8006ec14();

	DAT_800d13d4 = 20;
	Flash_Reset__Fv();

	if (type == 1)
		Pack_Init640x480__Fv();
	else
		Pack_Init__Fv();

	FUN_8004b038();
	FUN_8004aa6c();
	Font_Reset__Fv();
	Pad_LockAnalog__Fv();
}
