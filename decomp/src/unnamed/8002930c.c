/* __8CFlatBit (0x8002930c) */
extern char DAT_8009f7d0[];

char DAT_800d18d0[8];

char *__7CFT4Bit(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *__8CFlatBit(char *p) {
	__7CFT4Bit(p);

	*(char **)(p + 68) = DAT_8009f7d0;
	AttachTo__4CBitPv(p, DAT_800d18d0);

	p[109] = 32;
	*(short *)(p + 102) = 1;
	*(int *)(p + 104) = 0x10001000;
	return p;
}
