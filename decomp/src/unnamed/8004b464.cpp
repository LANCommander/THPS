/* FUN_8004b464 (0x8004b464) */
/* C++ (PAL). Positional variant of FUN_8004b250: left/right volumes come from the spatial
   attenuation at pos (12 bits each, scaled by the global percentage DAT_800d13cc). The
   attenuation's sign bit flips the left channel's phase. */
struct CVector {
	int vx, vy, vz;
};

extern int DAT_800b8a9c[];
extern int DAT_800d13cc;

int DAT_800d1acc;

unsigned int Utils_CalculateSpatialAttenuation(const CVector &, int, int);
extern "C" int playSFX__FUiUcssiUs(int, unsigned char, short, short, int);

extern "C" int FUN_8004b464(int id, const CVector &pos, int pan) {
	unsigned int att;
	int l, r, p, note;
	if (id < 0 || id == 0xffff)
		return 0;
	att = Utils_CalculateSpatialAttenuation(pos, 256, 12000);
	l = ((att & 0xfff) * DAT_800d13cc) >> 14;
	r = (((att >> 16) & 0xfff) * DAT_800d13cc) >> 14;
	if ((int)att < 0)
		l = -l;
	p = DAT_800b8a9c[id * 2 + 1];
	note = 60;

	if (p & 0xffff0000) {
		note = p >> 16;
		p &= 0xffff;
	}

	DAT_800d1acc = p;

	return playSFX__FUiUcssiUs(DAT_800b8a9c[id * 2], note, l * p / 100, r * p / 100, pan);
}
