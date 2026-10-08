/* InitStatsSwisch__Fv (0x8001648c) */
extern int DAT_800a5d0c[];
extern int DAT_800a5cec[];

void InitStatsSwisch(void) {
	int i;

	for (i = 0; i < 8; i++) {
		int v = (4 - i) * 30;

		DAT_800a5cec[i] = -100 - v;
		DAT_800a5d0c[i] = v + 612;
	}
}
