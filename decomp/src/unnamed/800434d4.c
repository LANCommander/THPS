/* FUN_800434d4 (0x800434d4) */
int *Mem_NewX__FUiii(unsigned n, int a, int b);

int *FUN_800434d4(unsigned n) {
	int *r = Mem_NewX__FUiii(n, 0, 1);
	int *q = r;
	unsigned c = (n + 3) >> 2;
	unsigned i;

	for (i = 0; i < c; i++)
		*q++ = 0;

	return r;
}
