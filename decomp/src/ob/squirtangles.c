/* SquirtAngles__5CBodyPs (0x800439ec) */
short *SquirtAngles__5CBodyPs(char *t, short *p) {
	*(short *)(t + 0x10) = *p++;
	*(short *)(t + 0x12) = *p++;
	*(short *)(t + 0x14) = *p++;
	return p;
}
