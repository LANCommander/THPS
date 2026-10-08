/* Die__8CPowerUp (0x8001ff44) */
int FUN_80043ce8(char *);
void FUN_8001fe7c(char *);

void Die__8CPowerUp(char *t) {
	if (!FUN_80043ce8(t)) {
		*(unsigned short *)(t + 0x52) |= 0x40;
		FUN_8001fe7c(t);
	}
}
