/* DisplayLabels__6CamPosUsUsUcUcUc (0x8007d4b4) */
void Font_String__FUsUsPcUcUcUcUc(unsigned short x, unsigned short y, char *s, unsigned char a,
                                  unsigned char b, unsigned char c, unsigned char d);

extern char DAT_800d20a8[], DAT_800d20b0[], DAT_800d20b4[], DAT_800d20b8[], DAT_800d20bc[],
    DAT_800a3534[], DAT_800a3544[];

void DisplayLabels__6CamPosUsUsUcUcUc(unsigned short x, unsigned short y, unsigned char r,
                                      unsigned char g, unsigned char b) {
	unsigned short x2;

	Font_String__FUsUsPcUcUcUcUc(x, y, DAT_800d20a8, r, g, b, 0);

	x2 = x + 20;
	Font_String__FUsUsPcUcUcUcUc(x2, y + 8, DAT_800d20b0, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x2, y + 16, DAT_800d20b4, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x2, y + 24, DAT_800d20b8, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x, y + 40, DAT_800d20bc, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x, y + 48, DAT_800a3534, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x, y + 56, DAT_800a3544, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x2, y + 64, DAT_800d20b0, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x2, y + 72, DAT_800d20b4, r, g, b, 0);
	Font_String__FUsUsPcUcUcUcUc(x2, y + 80, DAT_800d20b8, r, g, b, 0);
}
