/* unpack__6Sprite (0x80063cec) */
void unpack__11SlicedImage(int a);

void unpack__6Sprite(int *p) {
	if (p[3] != 0) {
		p[3] = 0;
		unpack__11SlicedImage(p[5]);
	}
}
