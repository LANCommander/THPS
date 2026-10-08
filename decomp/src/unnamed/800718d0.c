/* FUN_800718d0 (0x800718d0) */
extern unsigned char Pad[];

int FUN_800718d0(void) {
	int i;

	for (i = 0; i < 2; i++) {
		if (Pad[i * 364 + 0x1] || Pad[i * 364 + 0x11] ||
		    Pad[i * 364 + 0x41] || Pad[i * 364 + 0x51] ||
		    Pad[i * 364 + 0x61] || Pad[i * 364 + 0x71] ||
		    Pad[i * 364 + 0x81] || Pad[i * 364 + 0x91] ||
		    Pad[i * 364 + 0xa1] || Pad[i * 364 + 0xb1] ||
		    Pad[i * 364 + 0x21] || Pad[i * 364 + 0xf1])
			return 1;
	}

	return i < 2;
}
