/* Die__6CBaddy (0x8003fb1c) */
int IsDead__C5CBody(char *);
void SendDeathPulse__6CBaddy(char *);

void Die__6CBaddy(char *t) {
	if (!IsDead__C5CBody(t)) {
		SendDeathPulse__6CBaddy(t);

		*(unsigned short *)(t + 0x52) |= 0x40;
		*(unsigned short *)t |= 0x41;
	}
}
