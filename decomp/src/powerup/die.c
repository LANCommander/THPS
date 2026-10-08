/* Die__8CPowerUp (0x8001ff44) */
int IsDead__C5CBody(char *);
void DontDisplay__8CPowerUp(char *);

void Die__8CPowerUp(char *t) {
	if (!IsDead__C5CBody(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		DontDisplay__8CPowerUp(t);
	}
}
