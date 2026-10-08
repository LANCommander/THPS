/* CommonSwitchOnMenuCode__Fv (0x8001a128) */
#include "names.h"
extern char DAT_800c0a48[];

int DAT_800d1428;

extern int DAT_800a5f14[];

int DAT_800d140c;

extern int DAT_800d1e48;

int DAT_800d1514;

void Pad_ClearTriggers(char *p);
int CMenu_FindEntry(int m, int c);
void CMenu_SetLine(int m, unsigned char c);
void Mess_DeleteAll(void);
void Pad_ActuatorOff(unsigned char a, unsigned char b);
void SFX_Pause(void);
void SFX_PlayX(int a, int b, int c);

void CommonSwitchOnMenuCode(void) {
	char *s = DAT_800c0a48;

	Pad_ClearTriggers(s);
	Pad_ClearTriggers(s + 364);

	DAT_800d140c = 1;
	CMenu_SetLine(DAT_800d1428, CMenu_FindEntry(DAT_800d1428, DAT_800a5f14[0]));
	Mess_DeleteAll();
	Pad_ActuatorOff(0, 0);
	Pad_ActuatorOff(0, 1);
	SFX_Pause();
	SFX_PlayX(2, 4096, 0);

	DAT_800d1e48 = 0;
	DAT_800d1514 = 0;
}
