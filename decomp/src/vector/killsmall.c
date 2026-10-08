void f(int *p) {
	if ((unsigned)(p[0] + 0x800) < 0x1001)
		p[0] = 0;

	if ((unsigned)(p[1] + 0x800) < 0x1001)
		p[1] = 0;

	if ((unsigned)(p[2] + 0x800) < 0x1001)
		p[2] = 0;
}
