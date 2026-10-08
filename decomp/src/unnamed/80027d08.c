/* FUN_80027d08 (0x80027d08) */
int DAT_800d186c;

void *FUN_8004d068(unsigned int, int, int);

void *FUN_80027d08(unsigned int size) {
	int *p;
	unsigned int i, n;

	if (DAT_800d186c)
		p = FUN_8004d068(size, 0, 1);
	else
		p = FUN_8004d068(size, 0, 1);

	n = (size + 3) >> 2;

	{
		int *q = p;

		for (i = 0; i < n; i++)
			*q++ = 0;
	}

	return p;
}
