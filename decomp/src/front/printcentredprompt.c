/* Front_PrintCentredPrompt__FPCc (0x80017a30) */
typedef struct {
	int pad[2];
} SAnimFrame;

SAnimFrame *DAT_800d1420;

void Mess_SetTextJustify__FUc(int);
void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawText__FiiPCciUiib(int, int, const char *, int, int, int, int);
void *Panel_DrawTexturedPoly__FP10SAnimFrame(SAnimFrame *);
void Panel_SetStretchedScreenCoords__FiiP8POLY_FT4P10SAnimFrame(int, int, void *, SAnimFrame *);

void Front_PrintCentredPrompt(const char *s) {
	void *p;

	Mess_SetTextJustify__FUc(1);
	Mess_SetScale__Fi(192);
	Mess_SetRGB__FUcUcUci(150, 100, 25, 0);
	Mess_DrawText__FiiPCciUiib(227, 214, s, 0, 0, 256, 0);

	p = Panel_DrawTexturedPoly__FP10SAnimFrame(DAT_800d1420);

	if (p)
		Panel_SetStretchedScreenCoords__FiiP8POLY_FT4P10SAnimFrame(192, 211, p, DAT_800d1420);
}
