/* Trick_Bail__6CBruce (0x8002f774) */
#include "names.h"
typedef struct {
	int w;
	int p[4];
} L;

typedef struct {
	char p0[0x250];
	int f250, f254;
	char p258[0x284 - 0x258];
	int f284, f288;
	char p28c[0x2dc - 0x28c];
	int f2dc, f2e0;
	char p2e4[0x328 - 0x2e4];
	int f328, f32c, f330;
	char p334[0x364 - 0x334];
	int f364, f368;
	char p36c[0x428 - 0x36c];
	int a[80];
	int b[80];
} O;

extern int GGame;

extern void FUN_80042700(void *, int, int, int, int);
extern int Mips_CVecDotProd(void *, void *);
extern int FUN_8008b5dc(int);
extern void FUN_80010f70(int);
extern void FUN_80010eb8(int);
extern void FUN_8006e22c(void *);
extern void CBruce_Vibrate(void *, int, int, int);

void CBruce_Trick_Bail(O *oo) {
	char *o = (char *)oo;
	int i, sum, n, k, t, r, n2;
	volatile int pad[2];
	int *p, *q;

	if (GGame == 7)
		*(int *)(o + 0x330) = 0;

	*(int *)(o + 0x760) = 0;
	*(int *)(o + 0x32c) = 0;
	*(int *)(o + 0x328) = 0;
	*(int *)(o + 0x2dc) = 0;
	*(int *)(o + 0x2e0) = 0;
	*(int *)(o + 0x720) = 0;
	*(int *)(o + 0x288) = 0;
	*(int *)(o + 0x284) = 0;
	*(int *)(o + 0x250) = 0;
	*(int *)(o + 0x254) = 0;
	FUN_80042700(o, 0, 0, 0, 10);

	t = FUN_8008b5dc(Mips_CVecDotProd(o + 0x6c, o + 0x6c)) << 6;
	i = 0;
	sum = 0;
	n = *(int *)(o + 0xcac);

	if (n > 0) {
		p = (int *)(o + 0xb20);

		do {
			sum += *p;
			p += 5;
			i++;
		} while (i < n);
	}

	k = *(int *)(o + 0x32c);
	n2 = n * 2;

	if (k < 3)
		r = sum * (n2 + k) / 2;
	else
		r = (sum * (n2 + (k * 2 - 2))) >> 1;

	if (r != 0)
		FUN_80010f70(r);
	else
		FUN_80010eb8(t >> 12);

	for (i = 0; i < 80; i++) {
		oo->a[i] -= oo->b[i];
		oo->b[i] = 0;
	}

	FUN_8006e22c(o);

	*(int *)(o + 0x364) = 0;
	*(int *)(o + 0x368) = 0;
	CBruce_Vibrate(o, 8, 1, 150);
}
