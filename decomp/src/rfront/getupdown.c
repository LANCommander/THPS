/* GetUpDown__Fv (0x80011240) */
extern unsigned char Pad[];
extern int LeftRightAutoRepeatTimer;

int GetUpDown(void) {
	int r = 0;

	if (Pad[0xa0] || Pad[0x20c] || Pad[0xb0] || Pad[0x21c]) {
		if (LeftRightAutoRepeatTimer == 0 || (LeftRightAutoRepeatTimer >= 16 && (LeftRightAutoRepeatTimer & 3) == 0)) {
			if (Pad[0xb0] || Pad[0x21c])
				r = 1;

			if (Pad[0xa0] || Pad[0x20c])
				r = -1;
		}

		LeftRightAutoRepeatTimer++;
	} else {
		LeftRightAutoRepeatTimer = 0;
	}

	return r;
}
