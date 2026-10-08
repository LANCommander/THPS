/* RGBRed__Fv (0x800111e8) */
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);

void RGBRed(void) {
	Mess_SetRGB__FUcUcUci(96, 96, 96, 0);
}
