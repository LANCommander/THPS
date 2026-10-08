/* SetTint__7CFT4BitUcUcUc (0x800280c4) */
void SetTint__7CFT4BitUcUcUc(char *t, unsigned char r, unsigned char g, unsigned char b) {
	*(unsigned *)(t + 0x4c) = (*(unsigned *)(t + 0x4c) & 0xff000000) | (b << 16) | (g << 8) | r;
}
