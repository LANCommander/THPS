/* Pause__Fi (0x800478f4) */
volatile unsigned Vblanks;

void Pause(int n) {
	unsigned t = Vblanks + n;

	while (Vblanks < t)
		;
}
