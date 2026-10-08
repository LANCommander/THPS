/* MaybeFlipAnimationTransition__6CBruce (0x8002fc0c) */
void MaybeFlipAnimationTransition__6CBruce(char *p) {
	int a, b, c, d, e, f;

	if (*(int *)(p + 752)) {
		*(int *)(p + 752) = 0;
		*(int *)(p + 308) ^= 2;
	}

	if (*(int *)(p + 756)) {
		*(int *)(p + 756) = 0;
		a = -*(unsigned short *)(p + 2008);
		*(short *)(p + 1936) = a;
		*(int *)(p + 2008) = (short)a;
		b = -*(unsigned short *)(p + 2012);
		*(short *)(p + 1942) = b;
		*(int *)(p + 2012) = (short)b;
		d = -*(unsigned short *)(p + 2016);
		*(short *)(p + 1948) = d;
		*(int *)(p + 2016) = (short)d;
		e = -*(unsigned short *)(p + 2020);
		*(short *)(p + 1932) = e;
		*(int *)(p + 2020) = (short)e;
		c = -*(unsigned short *)(p + 2024);
		*(short *)(p + 1938) = c;
		*(int *)(p + 2024) = (short)c;
		f = -*(unsigned short *)(p + 2028);
		*(short *)(p + 1944) = f;
		*(int *)(p + 2028) = (short)f;
	}
}
