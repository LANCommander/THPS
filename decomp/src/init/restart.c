/* Init_Restart__F13EPackInitTypei (0x80071e88) */
#include "names.h"
extern int DAT_800d1150, DAT_800d114c, DAT_800d13d4;

void Init_Cleanup(int);
void Init_ResetMemory(int);
void Db_Reset(void);
void Spool_Init(void);
void Flash_Reset(void);
void Pack_Init640x480(void);
void Pack_Init(void);
void SFX_InitAtStart(void);
void Pal_Init(void);
void Font_Reset(void);
void Pad_LockAnalog(void);

void Init_Restart(int type, int b) {
	DAT_800d1150 = 0;
	DAT_800d114c = 0;
	Init_Cleanup(0);
	Init_ResetMemory(b);
	Db_Reset();
	Spool_Init();

	DAT_800d13d4 = 20;
	Flash_Reset();

	if (type == 1)
		Pack_Init640x480();
	else
		Pack_Init();

	SFX_InitAtStart();
	Pal_Init();
	Font_Reset();
	Pad_LockAnalog();
}
