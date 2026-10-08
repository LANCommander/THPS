/* FUN_8004fe28 (0x8004fe28) */
extern char DAT_800a1360[];
extern char DAT_800a136c[];
extern char DAT_800a1378[];
extern char DAT_800c0a48[];

int DAT_800d1b98[1];

void Mess_SetTextJustify__FUc(int);
int FUN_8001dc9c(char *);
void Mess_DrawText__FiiPCciUiib(int, int, char *, int, int, int, int);
void FUN_800242cc(void);
void FUN_800491e8(void);
void FUN_80049474(void);
void FUN_800494dc(void);
void FUN_8004b250(int, int, int);
int FileIO_Open__FPCc(char *);
void FUN_8004cb10(char *);
void FUN_8004cdd0(void);
char *Mem_NewX__FUiii(int, int, int);
void FUN_8004d5d0(char *);
void FUN_8005027c(int, int, int);
void FUN_8005c780(void);
void DrawColoredBox__FiiiiUcUcUc(int, int, int, int, int, int, int);
void SetClippingBox__Fiiii(int, int, int, int);
void FUN_80061ea0(void);
void FUN_8006af64(void);
void FUN_80070ff4(void);
void FUN_8008eebc(int);
void Front_ClearScreen__Fv(void);
void Mess_LoadFont__FPciii(char *, int, int, int);
void Mess_SetRGB__FUcUcUci(int, int, int, int);
void Mess_SetScale__Fi(int);
int Mess_TextHeight__FPCc(char *);
void Mess_UnloadFont__Fv(void);
void Pack_DefragmentFully__Fv(void);
void Pad_ClearTriggers__FP8SControl(char *);

void FUN_8004fe28(int a0, int a1) {
	char *s0;
	char *a2;

	char (*out)[30];
	unsigned char *p;
	int c;
	int y, s7, i, s6, s3, s4, s2, th, bot, top, off, tog, s0i;

	if (a1)
		FUN_8006af64();
	else
		Front_ClearScreen__Fv();

	Pack_DefragmentFully__Fv();

	if (a0 == 0)
		s0i = FileIO_Open__FPCc(DAT_800a1360);

	if (a0 == 1)
		s0i = FileIO_Open__FPCc(DAT_800a136c);

	s0 = Mem_NewX__FUiii(s0i, 1, 1);
	FUN_8004cb10(s0);

	s7 = 0;
	FUN_8004cdd0();

	out = (char (*)[30])Mem_NewX__FUiii(12000, 1, 1);
	p = (unsigned char *)s0;

	while (1) {
		c = *p;

		if ((unsigned char)c == 35)
			break;

		a2 = out[s7];
		i = 0;

		if ((unsigned char)c != 13) {
			for (;;) {
				if (c != 35) {
					a2[i] = c;
					i++;
					p++;

					if (i < 29) {
						c = *p;

						if (c != 13)
							continue;
					}
				}

				break;
			}
		}

		a2[i] = 0;

		if (*p == 13)
			p += 2;

		s7++;

		if (s7 < 400)
			continue;

		break;
	}

	FUN_8004d5d0(s0);
	Mess_LoadFont__FPciii(DAT_800a1378, -1, -1, -1);
	Mess_SetTextJustify__FUc(0);
	Mess_SetScale__Fi(255);
	Mess_SetRGB__FUcUcUci(150, 100, 25, 0);

	s6 = 0;
	s3 = FUN_8001dc9c((char *)out) + 256;
	th = Mess_TextHeight__FPCc((char *)out) + 8;
	bot = -th;
	top = s3;
	off = a0 * 4;
	s4 = *(int *)((char *)DAT_800d1b98 + off);
	Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
	Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);
	FUN_800491e8();

	tog = 0;
	FUN_8005027c(a0, 0, a1);

	while (1) {
		s2 = s6;
		FUN_8005c780();
		FUN_80049474();
		FUN_80061ea0();
		SetClippingBox__Fiiii(0, tog << 8, 512, 240);
		DrawColoredBox__FiiiiUcUcUc(0, 0, 512, 240, 0, 0, 0);

		tog = 1 - tog;

		if (!(s6 < s7))
			break;

		y = s3;

		while (y < top) {
			Mess_DrawText__FiiPCciUiib(256, y, out[s2], 1, 0, 256, 0);

			s2++;
			y += th;

			if (!(s2 < s7))
				break;
		}

		s4--;

		if (s4 == 0) {
			s3--;
			s4 = *(int *)((char *)DAT_800d1b98 + off);
		}

		if (s3 < bot) {
			s6++;
			s3 += th;
		}

		FUN_8008eebc(0);
		FUN_8005027c(a0, 1, a1);
		FUN_8008eebc(0);
		FUN_800494dc();
		FUN_80070ff4();
		FUN_800242cc();

		if (DAT_800c0a48[49] || DAT_800c0a48[413] || DAT_800c0a48[225] || DAT_800c0a48[589] ||
		    DAT_800c0a48[241] || DAT_800c0a48[605]) {
			Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
			Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);
			FUN_8004b250(145, 8192, 0);
			break;
		}
	}

	FUN_8005027c(a0, 2, a1);
	FUN_8004d5d0((char *)out);
	Mess_UnloadFont__Fv();
}
