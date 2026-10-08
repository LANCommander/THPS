/* FUN_8004b250 (0x8004b250) */
/* C++ (PAL). Plays sound effect id at a volume (clamped to 16384): records it for replays, then
   keys the VAB voice. Each table entry is {voice, note:16 | pitch:16}. A note of 0 means 60
   (middle C). The pitch is scaled by the global percentage DAT_800d13cc. */
extern int DAT_800b8a9c[];
extern int DAT_800d13cc;

int DAT_800d1acc;

void Video_SFXPlay(int, short, int);
extern "C" int playSFX__FUiUcssiUs(int, unsigned char, short, short, int);

extern "C" int FUN_8004b250(int id, short vol, int pan) {
	int p, note, v, i;
	if (id < 0 || id == 0xffff)
		return 0;
	if (vol > 16384)
		vol = 16384;
	i = id * 2;

	if (DAT_800b8a9c[i] >= 0)
		Video_SFXPlay(id, vol, pan);

	p = DAT_800b8a9c[i + 1];
	note = 60;

	if (p & 0xffff0000) {
		note = p >> 16;
		p &= 0xffff;
	}

	DAT_800d1acc = p;
	p = DAT_800d13cc * p / 100;
	v = (vol * p * 4) >> 16;

	return playSFX__FUiUcssiUs(DAT_800b8a9c[i], note, v, v, pan);
}
