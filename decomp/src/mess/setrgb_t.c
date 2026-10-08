unsigned DAT_800d15f4;

void f(unsigned r, unsigned g, unsigned b, int flag) {
	unsigned _a = 0xff & b;
	unsigned _b = g & 0xff;
	unsigned _c = r & 0xff;
	unsigned c = ((_a) << 16) | ((_b) << 8) | (_c);

	DAT_800d15f4 = c;
	DAT_800d15f4 = c | (flag ? 0x2e000000u : 0x2c000000u);
}
