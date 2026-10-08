/* IsDead__C5CBody (0x80043ce8) */
int IsDead__C5CBody(char *p) {
	unsigned x = *(unsigned short *)(p + 82) & 64;

	return x != 0;
}
