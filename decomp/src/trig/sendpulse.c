/* Trig_SendPulse__FPUs (0x80045718) */
void Trig_SendPulseToNode__Fi(int n);

void Trig_SendPulse(unsigned short *p) {
	int i, n = p[0];
	unsigned short *q = p + 1;

	i = 0;

	while (i < n) {
		i++;
		Trig_SendPulseToNode__Fi(*q++);
	}
}
