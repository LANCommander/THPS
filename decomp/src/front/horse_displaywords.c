/* Horse_DisplayWords__FPi (0x8001631c) */
void Mess_SetScale__Fi(int);
void Mess_SetTextJustify__FUc(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText__FiiPCciUiib(int, int, char *, int, int, int, int);

extern char DAT_800a7204[], DAT_8009e304[], DAT_8009e310[];

void Horse_DisplayWords__FPi(int *p) {
	char buf[32];
	int i;

	Mess_SetScale__Fi(256);
	Mess_SetTextJustify__FUc(0);

	for (i = 0; i < 2; i++) {
		char *s = DAT_800a7204;
		char *o = buf;
		int n = p[i];

		if (*s) {
			do {
				if (n) {
					n--;
					*o++ = *s++;
				} else {
					*o++ = '-';
					s++;
				}
			} while (*s);
		}

		*o = 0;

		if (i == 0) {
			Mess_SetRGB__FUcUcUci(80, 80, 128, 0);
			Mess_DrawText__FiiPCciUiib(86, 32, DAT_8009e304, 0, 0, 256, 0);
		} else {
			Mess_SetRGB__FUcUcUci(128, 80, 80, 0);
			Mess_DrawText__FiiPCciUiib(426, 32, DAT_8009e310, 0, 0, 256, 0);
		}

		Mess_DrawText__FiiPCciUiib(426 - (1 - i) * 340, 48, buf, 0, 0, 256, 0);
	}
}
