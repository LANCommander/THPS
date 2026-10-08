/* FUN_8001e07c (0x8001e07c) */
void FUN_8001e07c(unsigned short *p) {
	int i;

	for (i = 0; i < 32; i++) {
		*p = *p - 1;
		p++;
	}
}
