/* getPress__9PadBuffer (0x80064274) */
int getPress__9PadBuffer(int *p) {
	int r = 0;

	if (p[1] > 0) {
		int i = p[67];
		int *q;

		p[1] = p[1] - 1;
		q = p + i;
		r = q[3];
		i++;
		p[67] = i;

		if (i >= 8)
			p[67] = 0;
	}

	return r;
}
