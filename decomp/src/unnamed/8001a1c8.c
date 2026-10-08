/* FUN_8001a1c8 (0x8001a1c8) */
extern int DAT_800bf318[];
extern int DAT_800bf3d8[];
extern char *DAT_800a5f14[];
extern char DAT_800c0a48[];
extern char *DAT_800d19a4;
extern int DAT_800d1e48;

int DAT_800d1524;
int DAT_800d1528;
int DAT_800d152c;
int DAT_800d13e8;
int DAT_800d140c;
char *DAT_800d1428;

void Video_Stop__FP6CBruce(char *b);
void Pad_ClearTriggers__FP8SControl(char *p);
int FindEntry__5CMenuPCc(char *m, char *s);
void SetLine__5CMenuUc(char *m, unsigned char l);
void Mess_DeleteAll__Fv(void);
void Pad_ActuatorOff__FUcUc(unsigned char a, unsigned char b);
void SFX_Pause__Fv(void);
void SFX_PlayX__FUisi(int a, int b, int c);

void FUN_8001a1c8(void) {
	char *s;

	DAT_800d1524 = 0;
	DAT_800d1528 = 0;
	DAT_800d152c = 0;
	s = *(char **)(DAT_800d19a4 + 28);

	if (DAT_800bf318[0])
		Video_Stop__FP6CBruce(DAT_800d19a4);

	if (s && DAT_800bf3d8[0])
		Video_Stop__FP6CBruce(s);

	DAT_800d13e8 = 19;
	Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
	Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);

	DAT_800d140c = 1;
	SetLine__5CMenuUc(DAT_800d1428, FindEntry__5CMenuPCc(DAT_800d1428, DAT_800a5f14[0]));
	Mess_DeleteAll__Fv();
	Pad_ActuatorOff__FUcUc(0, 0);
	Pad_ActuatorOff__FUcUc(0, 1);
	SFX_Pause__Fv();
	SFX_PlayX__FUisi(2, 4096, 0);

	DAT_800d1e48 = 0;
}
