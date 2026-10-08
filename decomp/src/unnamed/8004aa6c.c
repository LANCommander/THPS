/* Pal_Init__Fv (0x8004aa6c) */
#include "names.h"
int DAT_800d1a80;
char DAT_800d1a8c[4];
char DAT_800d1a90[4];
char DAT_800d1a84[4];
char DAT_800d1a88[4];

extern char DAT_800d2a10[];
extern char DAT_800d2b10[];

void Pack_Pack(int a, int b, int c, char *d, char *e, int f, int g, int h);

void Pal_Init(void) {
	int i;
	volatile int pad[2];

	DAT_800d1a80 = 0;
	Pack_Pack(-1, 256, 75, DAT_800d1a8c, DAT_800d1a90, 16, 0, 0);
	Pack_Pack(-1, 16, 256, DAT_800d1a84, DAT_800d1a88, 16, 0, 0);

	for (i = 0; i < 256; i++)
		DAT_800d2a10[i] = 1;

	DAT_800d2b10[0] = 0;

	for (i = 1; i < 75; i++)
		DAT_800d2b10[i] = 1;
}
