/* uWibble__FP15STexWibVertInfo (0x800851ec) */
typedef struct {
	char _0[2];
	unsigned char wib;
} STexWibVertInfo;

int DAT_800d21c4;

extern short DAT_800c7400[][64];

int uWibble(STexWibVertInfo *v) {
	int t = v->wib >> 4;
	int o = v->wib & 15;

	if (t != 0) {
		int i = (DAT_800d21c4 + o * 4) & 63;
		short *row = DAT_800c7400[t];

		return row[i];
	}

	return 0;
}
