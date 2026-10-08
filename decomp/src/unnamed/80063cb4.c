/* pack__6Sprite (0x80063cb4) */
int pack__11SlicedImage(int a);

void pack__6Sprite(int *p) {
	if (p[3] == 0) {
		p[3] = 1;
		pack__11SlicedImage(p[5]);
	}
}
