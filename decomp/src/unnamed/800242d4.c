/* Game_Over__Fv (0x800242d4) */
#include "names.h"
typedef struct {
	char p[0x1f0];
	int f1f0;
	char q[0x838 - 0x1f4];
	int f838;
} B;

int DAT_800d16a4, DAT_800d1784, DAT_800d1788, DAT_800d178c;
B *DAT_800d17c8;
B *DAT_800d17cc;

extern int DAT_800d1954, DAT_800d1958, DAT_800d195c, DAT_800d1960, DAT_800d1964, DAT_800d1968,
    DAT_800d196c, DAT_800d1970;

void Game_Over(void) {
	int a, b, c;

	if (DAT_800d16a4 == 8) {
		a = DAT_800d17cc->f1f0;
		b = DAT_800d17c8->f1f0;

		if (a != b) {
			if (b < a) {
				DAT_800d1964++;
				DAT_800d1958++;

				if (DAT_800d196c < 0)
					DAT_800d196c = 1;
				else
					DAT_800d196c++;

				DAT_800d195c = -DAT_800d196c;
			} else {
				DAT_800d1954++;
				DAT_800d1968++;

				if (DAT_800d195c < 0)
					DAT_800d195c = 1;
				else
					DAT_800d195c++;

				DAT_800d196c = -DAT_800d195c;
			}

			c = DAT_800d17c8->f1f0;

			if (DAT_800d1960 < c)
				DAT_800d1960 = c;

			c = DAT_800d17cc->f1f0;

			if (DAT_800d1970 < c)
				DAT_800d1970 = c;
		}
	}

	if (DAT_800d1784 == 0) {
		DAT_800d1784 = 1;
		DAT_800d1788 = 80;
		DAT_800d178c = 64;

		if (DAT_800d17cc)
			DAT_800d17cc->f838 = 0;
	}
}
