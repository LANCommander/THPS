/* Video_BloodSplat__FP6CBruceii (0x80068ee8) */
#include "names.h"
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

int DAT_800d1dfc, DAT_800d1e00;

void Video_BloodSplat(CBruce *b, int a, int c) {
	if (DAT_800bf318[0].state == 1) {
		if (b == DAT_800d19a4)
			DAT_800d1dfc = a;
		else
			DAT_800d1e00 = a;
	}
}
