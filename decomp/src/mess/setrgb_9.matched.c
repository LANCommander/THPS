unsigned DAT_800d15f4;

void f(unsigned r, unsigned g, unsigned b, int flag) {
	unsigned _t9966 = 0xff & r;
	unsigned _t738 = 0xff & g;
	unsigned _t2445 = b & 0xff;
	unsigned c = ((_t2445) << 16) | ((_t738) << 8) | (_t9966);

	DAT_800d15f4 = c;
	DAT_800d15f4 = c | (flag ? 0x2e000000u : 0x2c000000u);
}
