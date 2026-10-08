/* __11CMotionBlurRC7CVectorR7CVectorPciii (0x80029a0c) */
typedef struct V {
	int x, y, z;
} V;

extern char DAT_8009f758[];

char *__8CFlatBit(char *p);
void SetAnim__7CFT4BitPc(char *p, char *n);
void SetSemiTransparent__7CFT4Bit(char *p);

char *__11CMotionBlurRC7CVectorR7CVectorPciii(char *p, V *a, V *b, char *n, int s1, int s2, int s3) {
	__8CFlatBit(p);

	*(char **)(p + 68) = DAT_8009f758;
	*(V *)(p + 24) = *a;
	*(V *)(p + 36) = *b;
	SetAnim__7CFT4BitPc(p, n);
	SetSemiTransparent__7CFT4Bit(p);

	*(short *)(p + 94) = s1;
	*(short *)(p + 74) = s2;
	*(short *)(p + 72) = s3;
	return p;
}
