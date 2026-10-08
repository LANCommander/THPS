/* Video_HighlightStart__FP6CBruce (0x80068f84) */
typedef struct {
	int f0, f4, f8;
} CBruce;

typedef struct {
	int state, f4, f8, fc;
	unsigned *p;
	unsigned buf;
	int n;
	int f1c;
	char pad[0xa0];
} SVideoInfo;

extern SVideoInfo DAT_800bf318[];
extern CBruce *DAT_800d19a4;

int DAT_800d1dec, DAT_800d1e0c, DAT_800d1e14;

void Video_HighlightStart__FP6CBruce(CBruce *b) {
	SVideoInfo *v;

	if (b == DAT_800d19a4)
		v = &DAT_800bf318[0];
	else
		v = &DAT_800bf318[1];

	if (!DAT_800d1dec) {
		int t = v->f1c, x = b->f8;

		DAT_800d1dec = 1;
		DAT_800d1e0c = t;
		DAT_800d1e14 = x;
	}
}
