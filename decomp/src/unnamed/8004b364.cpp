/* SFX_PlayLR__FUissi (0x8004b364) */
/* C++ (PAL). Stereo variant of FUN_8004b250: plays sound effect id with separate left/right
   volumes (each clamped to 16384), scaled by the global percentage DAT_800d13cc. */
extern int DAT_800b8a9c[];
extern int DAT_800d13cc;

int DAT_800d1acc;

extern "C" int playSFX__FUiUcssiUs(int, unsigned char, short, short, int);

extern "C" int SFX_PlayLR__FUissi(int id, short l, short r, int pan) {
	int p, note;
	if (l > 16384)
		l = 16384;
	if (r > 16384)
		r = 16384;
	if (id < 0 || id == 0xffff)
		return 0;
	p = DAT_800b8a9c[id * 2 + 1];
	note = 60;

	if (p & 0xffff0000) {
		note = p >> 16;
		p &= 0xffff;
	}

	DAT_800d1acc = p;
	p = DAT_800d13cc * p / 100;

	return playSFX__FUiUcssiUs(DAT_800b8a9c[id * 2], note, (l * p * 4) >> 16, (r * p * 4) >> 16, pan);
}
