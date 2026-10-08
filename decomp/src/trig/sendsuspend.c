/* SendSuspend__FPP5CBodyi (0x80045e30) */
void Suspend__5CBodyPP5CBody(char *b, char **pp);

void SendSuspend(char **pp, int node) {
	char *b;

	for (b = *pp; b; b = *(char **)(b + 0x1c))
		if (*(unsigned short *)(b + 0xe2) == node)
			Suspend__5CBodyPP5CBody(b, pp);
}
