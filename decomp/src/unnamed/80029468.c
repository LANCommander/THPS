/* __6CPixel (0x80029468) */
extern char DAT_8009f7a0[];

char DAT_800d18d8[8];

char *__4CBit(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *__6CPixel(char *p) {
	__4CBit(p);

	*(char **)(p + 68) = DAT_8009f7a0;
	AttachTo__4CBitPv(p, DAT_800d18d8);
	return p;
}
