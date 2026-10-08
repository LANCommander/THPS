/* removeFromMemory__11SlicedImage (0x80062de8) */
void Mem_Delete__FPv(int a);

void removeFromMemory__11SlicedImage(int *p) {
	if (p[12] == 0) {
		p[12] = 1;
		Mem_Delete__FPv(p[5]);
	}
}
