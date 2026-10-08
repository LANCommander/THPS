/* Front_PrintDemo__Fv (0x800160bc) */
int DAT_800d13ec;

extern int DAT_800d1780;
extern char DAT_8009e2e0[];

void Mess_SetTextJustify__FUc(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText__FiiPCciUiib(int, int, const char *, int, int, int, int);

void Front_PrintDemo(void) {
	if (--DAT_800d13ec == 0)
		DAT_800d13ec = 48;

	if (DAT_800d13ec >= 13) {
		if (DAT_800d1780 == 2) {
			Mess_SetTextJustify__FUc(0);
			Mess_SetScale__Fi(255);
			Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
			Mess_DrawText__FiiPCciUiib(128, 35, DAT_8009e2e0, 1, 0, 256, 0);
			Mess_DrawText__FiiPCciUiib(384, 35, DAT_8009e2e0, 1, 0, 256, 0);
		} else {
			Mess_SetTextJustify__FUc(0);
			Mess_SetScale__Fi(255);
			Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
			Mess_DrawText__FiiPCciUiib(256, 35, DAT_8009e2e0, 1, 0, 256, 0);
		}
	}
}
