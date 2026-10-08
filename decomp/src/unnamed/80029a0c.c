/* __11CMotionBlurRC7CVectorR7CVectorPciii (0x80029a0c) */
typedef struct V {
	int x, y, z;
} V;

extern char DAT_8009f758[];

char *FUN_8002930c(char *p);
void SetAnim__7CFT4BitPc(char *p, char *n);
void FUN_800280b0(char *p);

char *__11CMotionBlurRC7CVectorR7CVectorPciii(char *p, V *a, V *b, char *n, int s1, int s2, int s3) {
	FUN_8002930c(p);

	*(char **)(p + 68) = DAT_8009f758;
	*(V *)(p + 24) = *a;
	*(V *)(p + 36) = *b;
	SetAnim__7CFT4BitPc(p, n);
	FUN_800280b0(p);

	*(short *)(p + 94) = s1;
	*(short *)(p + 74) = s2;
	*(short *)(p + 72) = s3;
	return p;
}
