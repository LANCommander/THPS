/* FUN_8001a128 (0x8001a128) */
extern char DAT_800c0a48[];

int DAT_800d1428;

extern int DAT_800a5f14[];

int DAT_800d140c;

extern int DAT_800d1e48;

int DAT_800d1514;

void Pad_ClearTriggers__FP8SControl(char *p);
int FindEntry__5CMenuPCc(int m, int c);
void SetLine__5CMenuUc(int m, unsigned char c);
void Mess_DeleteAll__Fv(void);
void Pad_ActuatorOff__FUcUc(unsigned char a, unsigned char b);
void SFX_Pause__Fv(void);
void FUN_8004b250(int a, int b, int c);

void FUN_8001a128(void) {
	char *s = DAT_800c0a48;

	Pad_ClearTriggers__FP8SControl(s);
	Pad_ClearTriggers__FP8SControl(s + 364);

	DAT_800d140c = 1;
	SetLine__5CMenuUc(DAT_800d1428, FindEntry__5CMenuPCc(DAT_800d1428, DAT_800a5f14[0]));
	Mess_DeleteAll__Fv();
	Pad_ActuatorOff__FUcUc(0, 0);
	Pad_ActuatorOff__FUcUc(0, 1);
	SFX_Pause__Fv();
	FUN_8004b250(2, 4096, 0);

	DAT_800d1e48 = 0;
	DAT_800d1514 = 0;
}
