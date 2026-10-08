/* Pause__Fi (0x800478f4) */
volatile unsigned DAT_800d1a20;

void Pause(int n) {
	unsigned t = DAT_800d1a20 + n;

	while (DAT_800d1a20 < t)
		;
}
