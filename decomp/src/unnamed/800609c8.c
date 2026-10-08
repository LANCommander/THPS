/* FUN_800609c8 (0x800609c8) */
extern int DAT_800bf318[];
extern int DAT_800a42f4[];
extern char DAT_800c0a48[];
extern int DAT_800d1104;

int DAT_800d2358, DAT_800d235c;

int Mess_GetFontScale__Fv(void);
void Pack_DefragmentFully__Fv(void);
void FUN_8001160c(int, int, int);
void FUN_80011628(int);
int FUN_8004d068(int, int, int);
void FUN_8005c780(void);
void FUN_8005c934(void);
void FUN_80070ff4(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void FUN_80064890(int, int, int);
void FUN_8001206c(void);
void FUN_8006b26c(void);
int FUN_800127c4(void);
void Pad_ClearTriggers__FP8SControl(char *);
void FUN_8004b250(int, int, int);
void Mess_SetFontScale__FUi(int);
void Front_RestoreBackground__Fv(void);
void erase__12VerticalMenu(int);
void FUN_8008c468(int);
void FUN_80011570(void);
void FUN_80011150(void);
void FUN_8004d5d0(int);

int FUN_800609c8(void) {
	int fs, i;

	fs = Mess_GetFontScale__Fv();
	Pack_DefragmentFully__Fv();
	FUN_8001160c(640, 15, 39);
	FUN_80011628(1);

	DAT_800bf318[1] = FUN_8004d068(640, 0, 1);
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

		FUN_8001206c();
		FUN_8006b26c();
	} while (FUN_800127c4() == 18);

	Pad_ClearTriggers__FP8SControl((char *)i);
	Pad_ClearTriggers__FP8SControl((char *)i + 364);
	FUN_8004b250(145, 8192, 0);
	Mess_SetFontScale__FUi(fs);

	i = 0;

	do {
		FUN_8006b240();
		FUN_80061ea0();
		Front_RestoreBackground__Fv();

		if (DAT_800d1104 != 0)
			erase__12VerticalMenu(DAT_800d1104);

		i++;
		FUN_8006b26c();
	} while (i < 2);

	FUN_8008c468(0);
	FUN_80011570();

	if (DAT_800d1104 != 0)
		FUN_80011150();

	FUN_8004d5d0(DAT_800bf318[1]);

	switch (DAT_800a42f4[0]) {
		case 1:
			return 0x611;
		case 2:
			return 0x612;
		default:
			return -1;
	}
}
