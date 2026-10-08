/* SetRGB__9CChunkBitUcUcUc (0x800289c8) */
int Redbook_Rnd__Fi(int n);

void SetRGB__9CChunkBitUcUcUc(char *t, unsigned char r, unsigned char g, unsigned char b) {
	int ri = r, gi = g, bi = b;
	int k;

	*(unsigned *)(t + 0xac) = (bi << 16) | (gi << 8) | ri;
	k = Redbook_Rnd__Fi(4096);
	*(unsigned *)(t + 0xb0) = (((bi * k) >> 12) << 16) | (((gi * k) >> 12) << 8) | ((ri * k) >> 12);
	k = Redbook_Rnd__Fi(4096);
	*(unsigned *)(t + 0xb4) = (((bi * k) >> 12) << 16) | (((gi * k) >> 12) << 8) | ((ri * k) >> 12);
	k = Redbook_Rnd__Fi(4096);
	*(unsigned *)(t + 0xb8) = (((bi * k) >> 12) << 16) | (((gi * k) >> 12) << 8) | ((ri * k) >> 12);
}
