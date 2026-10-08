/* __nw__5CItemUi (0x800241dc) */
void *Mem_NewX__FUiii(unsigned, int, int);

void *__nw__5CItemUi(unsigned size) {
	void *p = Mem_NewX__FUiii(size, 0, 1);
	int *q = p;
	unsigned i;

	for (i = 0; i < (size + 3) >> 2; i++)
		*q++ = 0;

	return p;
}
