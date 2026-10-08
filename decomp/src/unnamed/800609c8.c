/* FUN_800609c8 (0x800609c8) */
#include "names.h"
extern int DAT_800bf318[];
extern int DAT_800a42f4[];
extern char DAT_800c0a48[];
extern int DAT_800d1104;

int DAT_800d2358, DAT_800d235c;

int Mess_GetFontScale(void);
void Pack_DefragmentFully(void);
void Front_InitMemCardMenus(int, int, int);
void FUN_80011628(int);
int Mem_NewX(int, int, int);
void FUN_8005c780(void);
void FUN_8005c934(void);
void FUN_80070ff4(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_80064890(int, int, int);
void Front_MemCardHiResDisplay(void);
void FUN_8006b26c(void);
int Front_MemCardUpdate(void);
void Pad_ClearTriggers(char *);
void SFX_PlayX(int, int, int);
void Mess_SetFontScale(int);
void Front_RestoreBackground(void);
void VerticalMenu_erase(int);
void FUN_8008c468(int);
void FUN_80011570(void);
void FUN_80011150(void);
void Mem_Delete(int);

int FUN_800609c8(void) {
	int fs, i;

	fs = Mess_GetFontScale();
	Pack_DefragmentFully();
	Front_InitMemCardMenus(640, 15, 39);
	FUN_80011628(1);

	DAT_800bf318[1] = Mem_NewX(640, 0, 1);
	DAT_800a42f4[0] = 0;
	i = (int)DAT_800c0a48;

	do {
		FUN_8005c780();
		FUN_8005c934();
		FUN_80070ff4();
		FUN_8006b240();
		FUN_80061ea0();

		if (DAT_800d1104 != 0)
			FUN_80064890(DAT_800d1104, DAT_800d2358, DAT_800d235c);

		Front_MemCardHiResDisplay();
		FUN_8006b26c();
	} while (Front_MemCardUpdate() == 18);

	Pad_ClearTriggers((char *)i);
	Pad_ClearTriggers((char *)i + 364);
	SFX_PlayX(145, 8192, 0);
	Mess_SetFontScale(fs);

	i = 0;

	do {
		FUN_8006b240();
		FUN_80061ea0();
		Front_RestoreBackground();

		if (DAT_800d1104 != 0)
			VerticalMenu_erase(DAT_800d1104);

		i++;
		FUN_8006b26c();
	} while (i < 2);

	FUN_8008c468(0);
	FUN_80011570();

	if (DAT_800d1104 != 0)
		FUN_80011150();

	Mem_Delete(DAT_800bf318[1]);

	switch (DAT_800a42f4[0]) {
		case 1:
			return 0x611;
		case 2:
			return 0x612;
		default:
			return -1;
	}
}
