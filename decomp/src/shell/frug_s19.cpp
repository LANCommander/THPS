/* frug__FUi (0x800782b4) */
unsigned int DAT_800d1fec;

int arccos(int);

void frug(unsigned int n) {
	DAT_800d1fec ^= n;
	DAT_800d1fec = (DAT_800d1fec << 1) ^ (DAT_800d1fec >> 31);
	DAT_800d1fec = DAT_800d1fec * 521;
	DAT_800d1fec += arccos(DAT_800d1fec);
}
