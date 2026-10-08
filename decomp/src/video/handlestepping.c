/* Video_HandleStepping__Fv (0x8006ac84) */
typedef struct {
	unsigned char b[0x16c];
} Pad;

extern Pad DAT_800c0a48[];
extern unsigned char DAT_800c0a48b[];

extern struct {
	int mode;
	char _4[0xb8];
	int step;
} DAT_800bf318;

extern int DAT_800d1cb0, DAT_800d13e8, DAT_800d1780, DAT_800d16fc, DAT_800d1734;

int DAT_800d1df0;

void Video_HandleStepping__Fv(void) {
	int i, v;

	if (DAT_800bf318.mode != 2 || DAT_800d1cb0 == 0) {
		if (DAT_800d1cb0 != 0)
			return;

		for (i = 0; i < 2; i++) {
			if (DAT_800c0a48b[i * 364 + 1] || DAT_800c0a48b[i * 364 + 0x11] ||
			    DAT_800c0a48b[i * 364 + 0x41] || DAT_800c0a48b[i * 364 + 0x51] ||
			    DAT_800c0a48b[i * 364 + 0x61] || DAT_800c0a48b[i * 364 + 0x71] ||
			    DAT_800c0a48b[i * 364 + 0x81] || DAT_800c0a48b[i * 364 + 0x91] ||
			    DAT_800c0a48b[i * 364 + 0xa1] || DAT_800c0a48b[i * 364 + 0xb1] ||
			    DAT_800c0a48b[i * 364 + 0x21] || DAT_800c0a48b[i * 364 + 0xf1])
				DAT_800c0a48b[i * 364 + 0x31] = 1;
		}

		return;
	}

	if (DAT_800d13e8 == 20 || DAT_800d13e8 == 22 || DAT_800d13e8 == 21)
		return;

	if (DAT_800c0a48[0].b[0x11] || (DAT_800d1780 == 2 && DAT_800c0a48[1].b[0x11])) {
		v = DAT_800bf318.step;
		DAT_800c0a48[0].b[0x11] = 0;
		DAT_800c0a48[1].b[0x11] = 0;
		v ^= 1;
		DAT_800bf318.step = v;
		DAT_800d16fc = v;
		DAT_800d1734 = v;
	}

	if (DAT_800bf318.step == 0)
		return;

	DAT_800d16fc = 1;

	if (DAT_800c0a48[0].b[0x20] || (DAT_800d1780 == 2 && DAT_800c0a48[1].b[0x20])) {
		if (DAT_800d1df0 != 0) {
			DAT_800d1df0--;
			return;
		}

		DAT_800d1df0 = 6;
		DAT_800d16fc = 0;
		return;
	}

	if (DAT_800c0a48[0].b[0] || (DAT_800d1780 == 2 && DAT_800c0a48[1].b[0])) {
		if (DAT_800d1df0 != 0) {
			DAT_800d1df0--;
			return;
		}

		DAT_800d1df0 = 1;
		DAT_800d16fc = 0;
		return;
	}

	DAT_800d1df0 = 0;
	return;
}
