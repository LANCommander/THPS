/* __11CMotionBlurRC7CVectorR7CVectorPciii (0x80029a0c) */
#include "names.h"
typedef struct V {
	int x, y, z;
} V;

extern char DAT_8009f758[];

char *CFlatBit_ctor(char *p);
void CFT4Bit_SetAnim(char *p, char *n);
void CFT4Bit_SetSemiTransparent(char *p);

char *CMotionBlur_ctor(char *p, V *a, V *b, char *n, int s1, int s2, int s3) {
	CFlatBit_ctor(p);

	*(char **)(p + 68) = DAT_8009f758;
	*(V *)(p + 24) = *a;
	*(V *)(p + 36) = *b;
	CFT4Bit_SetAnim(p, n);
	CFT4Bit_SetSemiTransparent(p);

	*(short *)(p + 94) = s1;
	*(short *)(p + 74) = s2;
	*(short *)(p + 72) = s3;
	return p;
}
