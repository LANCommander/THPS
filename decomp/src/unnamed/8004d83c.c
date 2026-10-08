/* FUN_8004d83c (0x8004d83c) */
int FUN_8004d83c(int *a) {
	int *p = (int *)a[0];

	if (!p)
		return 0;

	if (p[-2] == a[1])
		return (int)p;

	a[0] = 0;
	return 0;
}
