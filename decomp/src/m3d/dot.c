unsigned f(int *a, int *b) {
	long long s = (long long)a[0] * b[0] + (long long)a[1] * b[1] + (long long)a[2] * b[2];
	return (unsigned)(s >> 12);
}
