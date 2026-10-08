short *f(short *p, const int *n) {
	p[0] = (short)((int)p[0] / *n);
	p[1] = (short)((int)p[1] / *n);
	p[2] = (short)((int)p[2] / *n);
	return p;
}
