/* FUN_8006d0c8 (0x8006d0c8) */
/* Panel: the current combo/score readout (PANEL.CPP), as C. Sums the pending trick scores, works out
   the multiplier, and draws the score and x-multiplier text. */
extern int DAT_800a71fc[];
extern int DAT_800bf318[];
extern char DAT_800d1e88[], DAT_800d1e8c[], DAT_800d1e94[];

unsigned DAT_800d1ec8;

extern void Mess_SetTextJustify__FUc(int);
extern void FUN_8001e0a4(void *, int);
extern void GraffitiColor__FP6CBruce(void *);
extern void TrickMessage__10CPanelData(void *);
extern void FUN_8008b900(char *, char *, int);
extern int Mess_DrawPanelText__FiiPCciUii(int, int, char *, int, int, int);
extern void Mess_SetRGB__FUcUcUci(int, int, int, int);
extern void Mess_SetScale__Fi(int);

void FUN_8006d0c8(char *o, int x0, int y0) {
	char b1[16];
	char b2[16];
	unsigned s2;
	int n2, s3, x, y, s5, s4, n, k, i, v, r;
	int *p;

	s2 = 0;
	s3 = 0;
	x = x0 & 0xffff;
	y = y0 & 0xffff;
	s5 = DAT_800bf318[0] != 2;

	if (DAT_800a71fc[0]) {
		n = *(int *)(o + 0xcac);

		if (n > 0) {
			k = *(int *)(o + 0x32c);
			n2 = n * 2;

			if (k < 3)
				v = n2 + k;
			else
				v = n2 + (k * 2 - 2);

			s3 = v;

			if (*(int *)(o + 0x734) == 2 && k == 1)
				s3 -= 1;

			for (i = 0; i < *(int *)(o + 0xcac); i++)
				s2 += ((int *)(o + 0xb20))[i * 5];
		}

		if (*(unsigned *)(o + 0xa64))
			s2 = *(unsigned *)(o + 0xa64);

		if (s2 || *(int *)(o + 0xa70) == 5) {
			FUN_8008b900(b1, DAT_800d1e88, *(int *)(o + 0xa70) == 5 ? DAT_800d1ec8 : s2);
			Mess_SetRGB__FUcUcUci(128, 128, 128, 0);
			GraffitiColor__FP6CBruce(o);

			s4 = s3 < 3;

			if (!s4)
				Mess_SetTextJustify__FUc(2);
			else
				Mess_SetTextJustify__FUc(0);

			Mess_SetScale__Fi(256);

			if (s5) {
				FUN_8001e0a4(o + 0xa88, *(int *)(o + 0xa70) == 5);
				Mess_DrawPanelText__FiiPCciUii(x, y, b1, 0, 0, 256);
				FUN_8001e0a4(o + 0xa88, 0);
			}

			if (*(int *)(o + 0xe18) > 0)
				*(int *)(o + 0xe18) = *(int *)(o + 0xe18) - 1;

			if (!s4) {
				if (s3 & 1)
					FUN_8008b900(b2, DAT_800d1e8c, s3 >> 1);
				else
					FUN_8008b900(b2, DAT_800d1e94, s3 >> 1);

				Mess_SetRGB__FUcUcUci(128, 128, 128, 0);
				GraffitiColor__FP6CBruce(o);
				Mess_SetTextJustify__FUc(1);
				Mess_SetScale__Fi(256);

				if (s5)
					Mess_DrawPanelText__FiiPCciUii(x, y, b2, 0, 0, 256);
			}

			if (s2)
				DAT_800d1ec8 = (s2 * s3) >> 1;
		}

		if (*(int *)(o + 0xcac)) {
			int kk = *(int *)(o + 0x32c);

			if (*(int *)(o + 0xddc) < kk) {
				if (*(int *)(o + 0x734) != 2 || kk >= 2) {
					TrickMessage__10CPanelData(o + 0x924);

					*(int *)(o + 0xddc) = *(int *)(o + 0x32c);
				}
			}
		}
	}
}
