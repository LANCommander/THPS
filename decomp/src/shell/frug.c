/* frug__FUi (0x800782b4) */
unsigned DAT_800d1fec;

int FUN_80035dc8(void);

void frug(unsigned n) {
	unsigned v = DAT_800d1fec ^ n;

	DAT_800d1fec = ((v << 1) ^ (v >> 31)) * 521;
	DAT_800d1fec += FUN_80035dc8();
}
