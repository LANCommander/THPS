/* FUN_8002357c (0x8002357c) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

int DAT_800d1650, DAT_800d1678, DAT_800d1634, DAT_800d164c, DAT_800d1630, DAT_800d1644,
    DAT_800d1640, DAT_800d163c;
short DAT_800d1688, DAT_800d168a;
int DAT_800d168c[2];

extern char *DAT_800d2044;
extern int DAT_800d140c, DAT_800d16fc, DAT_800d1734;
extern V DAT_800a6388[];
extern int DAT_800a6748[];

extern int Utils_CrapDist(void *, void *);
extern void FUN_80024010(void *);
extern void DecDCTvlcBuild3(void);
extern void FUN_800902c0(int, int);
extern void FUN_8009033c(int, int);
extern void FUN_8008f19c(int, int, int);
extern void FUN_8008f4d4(int, int, int);
extern void FUN_8008f0ec(int);
extern void strKickCD(void);
extern int strNextVlc(int);

void FUN_8002357c(int a) {
	int i, best, bi, d;
	V *p;

	if (DAT_800d1650) {
		DAT_800d1650 = DAT_800d1650 - 1;

		if (DAT_800d1650 == 0) {
			bi = 0;
			best = 0xffffff;

			for (i = 0; i < DAT_800d1678; i++) {
				d = Utils_CrapDist(DAT_800d2044 + 4, &DAT_800a6388[i]);

				if (d < best) {
					best = d;
					bi = i;
				}
			}

			FUN_80024010((char *)DAT_800a6388 + bi * 12);

			DAT_800d1650 = 4;
		}
	}

	if (DAT_800d1634) {
		int w;

		DecDCTvlcBuild3();

		if (DAT_800d164c == 0) {
			if (DAT_800d1630) {
				DAT_800d1630 = 0;
				strKickCD();
			}

			if (DAT_800d1644) {
				FUN_800902c0(DAT_800d168c[DAT_800d1640], 2);

				w = DAT_800d1688 * DAT_800d168a;
				DAT_800d1640 = 1 - DAT_800d1640;
				FUN_8009033c(DAT_800a6748[DAT_800d163c], w / 2);
			}

			DAT_800d1644 = strNextVlc(a);
		}

		if (DAT_800d140c || DAT_800d16fc || DAT_800d1734) {
			if (DAT_800d164c == 0) {
				DAT_800d164c = 1;
				FUN_8008f19c(1, 0, -1);
				FUN_8008f4d4(9, 0, 0);
			}
		} else if (DAT_800d164c) {
			DAT_800d164c = 0;
			FUN_8008f19c(0, 0, -1);
			FUN_8008f0ec(480);
		}
	}
}
