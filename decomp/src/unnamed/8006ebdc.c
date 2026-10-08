/* FUN_8006ebdc (0x8006ebdc) */
int FUN_8006ebdc(char *p) {
	int i, s = 0;
	int n = *(int *)(p + 904);

	for (i = 0; i < n; i++)
		s += *(int *)(p + 508 + i * 20);

	return s;
}
