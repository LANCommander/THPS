/* FUN_80063cec (0x80063cec) */
void unpack__11SlicedImage(int a);

void FUN_80063cec(int *p) {
	if (p[3] != 0) {
		p[3] = 0;
		unpack__11SlicedImage(p[5]);
	}
}
