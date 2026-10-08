/* Die__5CBody (0x80043cac) */
int IsDead__C5CBody(char *);

void Die__5CBody(char *t) {
	if (!IsDead__C5CBody(t))
		*(unsigned short *)(t + 0x52) |= 0x40;
}
