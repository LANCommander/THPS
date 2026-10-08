/* Shrink__7CFT4Biti (0x80028234) */
void Die__4CBit(char *);

int Shrink__7CFT4Biti(char *t, int kill) {
	if (*(short *)(t + 0x5e) == 0) {
		if (kill)
			Die__4CBit(t);

		return 1;
	}

	*(short *)(t + 0x5e) -= *(unsigned short *)(t + 0x4a);

	if (*(short *)(t + 0x5e) < 0)
		*(short *)(t + 0x5e) = 0;

	return 0;
}
