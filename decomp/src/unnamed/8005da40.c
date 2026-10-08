/* FUN_8005da40 (0x8005da40) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

typedef struct {
	struct VT *vt;
} O;

extern unsigned char DAT_800c0a48[];
extern char DAT_800c0a79[];
extern int DAT_800bf0dc[], DAT_800bf0e8[];
extern char DAT_800a1b84[], DAT_800bf220[];
extern int DAT_800d1a1c, DAT_800d1cb0;

int DAT_800d1ce8, DAT_800d1cec, DAT_800d1cf0, DAT_800d1d14;
O *DAT_800d1d0c;

void FUN_8008c468(int);
void FUN_8006b2f4(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_800242cc(void);
void SetClippingBox__Fiiii(int, int, int, int);
void draw__6Spriteiiiiii(O *, int, int, int, int, int, int);
void FUN_80070ff4(void);
int FUN_800718d0(void);
void FUN_8004b250(int, int, int);
void Pause__Fi(int);
void Pad_ClearTriggers__FP8SControl(unsigned char *);
void Mess_LoadFont__FPciii(char *, int, int, int);
void Mess_SetTextJustify__FUc(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(int, int, int, int);
void Mess_DrawText__FiiPCciUiib(int, int, char *, int, int, int, int);
void FUN_8006b26c(void);
void Mess_UnloadFont__Fv(void);

void FUN_8005da40(void) {
	FUN_8008c468(0);
	FUN_8006b2f4();
	FUN_8006b240();
	FUN_80061ea0();
	FUN_800242cc();
	SetClippingBox__Fiiii(0, 0, 512, 240);

	if (DAT_800d1d14) {
		DAT_800d1d14 = 0;
		draw__6Spriteiiiiii(DAT_800d1d0c, DAT_800bf0dc[0], DAT_800bf0e8[0], 0, -1, -1, -1);
	}

	FUN_80070ff4();

	if (FUN_800718d0())
		DAT_800c0a79[0] = 1;

	if (DAT_800c0a48[0x31] && DAT_800d1cb0 == 0) {
		FUN_8004b250(2, 0x2000, 0);
		Pause__Fi(20);
		Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
		Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);

		DAT_800d1ce8 = 0;
		DAT_800d1cf0 = 1;
	}

	if (DAT_800d1cec) {
		if (DAT_800d1d0c)
			DAT_800d1d0c->vt->fn((char *)DAT_800d1d0c + DAT_800d1d0c->vt->off, 3);

		if (DAT_800d1cb0 == 0) {
			DAT_800d1a1c = 64;
			return;
		}

		Mess_LoadFont__FPciii(DAT_800a1b84, -1, -1, -1);
		FUN_8006b240();
		FUN_80061ea0();
		Mess_SetTextJustify__FUc(0);
		Mess_SetScale__Fi(255);
		Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
		Mess_DrawText__FiiPCciUiib(256, 110, DAT_800bf220, 1, 0, 256, 0);
		Mess_DrawText__FiiPCciUiib(256, 130, DAT_800bf220 + 32, 1, 0, 256, 0);
		FUN_8006b26c();
		Mess_UnloadFont__Fv();
	}
}
