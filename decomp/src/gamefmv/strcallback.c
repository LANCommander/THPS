/* strCallback__Fv (0x80023d3c) */
#include "names.h"
typedef struct {
	short x, y, w, h;
} RECT;

extern int DAT_800a6748[];
extern int DAT_800d785c;

int DAT_800d163c, DAT_800d162c;
unsigned char DAT_800d167c, DAT_800d166c;
short DAT_800d1658, DAT_800d1686, DAT_800d168a;
RECT DAT_800d1684;
unsigned short DAT_800d1670, DAT_800d1688;

void FUN_8008f79c(void);
void FUN_8009033c(int, int);
void FUN_8008c714(RECT *, int);

void strCallback(void) {
	RECT r;
	int p;

	if (DAT_800d167c && DAT_800d785c) {
		FUN_8008f79c();

		DAT_800d785c = 0;
	}

	r = DAT_800d1684;
	p = DAT_800a6748[DAT_800d163c];
	DAT_800d163c++;

	if (DAT_800d163c >= DAT_800d166c)
		DAT_800d163c = 0;

	DAT_800d1684.x += DAT_800d1688;

	if (DAT_800d1684.x < DAT_800d1670) {
		FUN_8009033c(DAT_800a6748[DAT_800d163c], (short)DAT_800d1688 * DAT_800d168a / 2);
	} else {
		DAT_800d1684.x = DAT_800d1658;

		if (DAT_800d162c) {
			if (DAT_800d1686 < 256)
				DAT_800d1686 += 256;
			else
				DAT_800d1686 -= 256;
		}
	}

	if (DAT_800d1658 != -1)
		FUN_8008c714(&r, p);
}
