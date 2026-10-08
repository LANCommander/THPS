/* __nw__5CItemUi (0x800241dc) */
void *FUN_8004d068(unsigned, int, int);

void *__nw__5CItemUi(unsigned size) {
	void *p = FUN_8004d068(size, 0, 1);
	int *q = p;
	unsigned i;

	for (i = 0; i < (size + 3) >> 2; i++)
		*q++ = 0;

	return p;
}
