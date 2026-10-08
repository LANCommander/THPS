/* Video_Stop__FP6CBruce (0x8006981c) */
typedef struct CBruce CBruce;

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

int DAT_800d1de8;

void FlushBits__FP10SVideoInfo(SVideoInfo *);

void Video_Stop__FP6CBruce(CBruce *b) {
	SVideoInfo *v;

	if (b == DAT_800d19a4)
		v = &DAT_800bf318[0];
	else
		v = &DAT_800bf318[1];

	if (v->state == 1)
		FlushBits__FP10SVideoInfo(v);

	v->state = 0;
	DAT_800d1de8 = 0;
}
