/* Die__6CBruce (0x80042778) */
int IsDead__C5CBody(char *);

void Die__6CBruce(char *t) {
	if (!IsDead__C5CBody(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		*(unsigned short *)t |= 0x41;
	}
}
