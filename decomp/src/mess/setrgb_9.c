unsigned FlagsBGR;

void f(unsigned r, unsigned g, unsigned b, int flag) {
	unsigned c = ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);

	FlagsBGR = c;
	FlagsBGR = c | (flag ? 0x2e000000u : 0x2c000000u);
}
