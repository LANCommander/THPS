/* SetTransparency__8CQuadBitUc (0x800284ac) */
void SetTransparency__8CQuadBitUc(char *t, unsigned char a) {
	*(unsigned *)(t + 0x90) = (*(unsigned *)(t + 0x90) & 0xff000000) | (a << 16) | (a << 8) | a;
}
