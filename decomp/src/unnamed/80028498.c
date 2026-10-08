/* SetSemiTransparent__8CQuadBit (0x80028498) */
void SetSemiTransparent__8CQuadBit(char *p) {
	*(unsigned *)(p + 144) |= 0x2000000;
}
