/* GetUpDown__Fv (0x80011240) */
extern unsigned char DAT_800c0a48[];
extern int DAT_800d141c;

int GetUpDown(void) {
	int r = 0;

	if (DAT_800c0a48[0xa0] || DAT_800c0a48[0x20c] || DAT_800c0a48[0xb0] || DAT_800c0a48[0x21c]) {
		if (DAT_800d141c == 0 || (DAT_800d141c >= 16 && (DAT_800d141c & 3) == 0)) {
			if (DAT_800c0a48[0xb0] || DAT_800c0a48[0x21c])
				r = 1;

			if (DAT_800c0a48[0xa0] || DAT_800c0a48[0x20c])
				r = -1;
		}

		DAT_800d141c++;
	} else {
		DAT_800d141c = 0;
	}

	return r;
}
