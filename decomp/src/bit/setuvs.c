/* SetUVs__9CChunkBitUsUsUcUcUcUcUcUc (0x80028b1c) */
void SetUVs__9CChunkBitUsUsUcUcUcUcUcUc(char *t, unsigned short a, unsigned short b,
                                        unsigned char c, unsigned char d, unsigned char e,
                                        unsigned char f, unsigned char g, unsigned char h) {
	*(unsigned *)(t + 0xa0) = (a << 16) | (d << 8) | c;
	*(unsigned *)(t + 0xa4) = (b << 16) | (f << 8) | e;
	*(unsigned short *)(t + 0xa8) = (h << 8) | g;
}
