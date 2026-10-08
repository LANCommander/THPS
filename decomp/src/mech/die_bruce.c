/* Die__6CBruce (0x80042778) */
int FUN_80043ce8(char *);

void Die__6CBruce(char *t) {
	if (!FUN_80043ce8(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		*(unsigned short *)t |= 0x41;
	}
}
