/* M3dInit_SetResolution__FUiUi (0x800820e4) */
extern unsigned DAT_800d2188 __attribute__((section(".data"))),
    DAT_800d218c __attribute__((section(".data")));
extern unsigned DAT_800d2190 __attribute__((section(".data"))),
    DAT_800d2194 __attribute__((section(".data")));

void M3dInit_SetResolution(unsigned w, unsigned h) {
	DAT_800d2188 = w;
	DAT_800d218c = h;

	if (w * 3 > h * 4) {
		DAT_800d2190 = 4096;
		DAT_800d2194 = (w * 3 << 12) / (h * 4);
	} else {
		DAT_800d2194 = 4096;
		DAT_800d2190 = (h * 4 << 12) / (w * 3);
	}
}
