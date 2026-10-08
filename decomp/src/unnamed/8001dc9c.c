/* Mess_TextHeightAboveBaseline__FPCc (0x8001dc9c) */
#include "names.h"
typedef struct {
	int **p;
	char pad[32];
} A;

typedef struct {
	char pad[20];
	int *p;
	char pad2[2];
	unsigned short h;
	char pad3[8];
} B;

extern A DAT_800a6124[];
extern B DAT_800a6110[];

unsigned char DAT_800d1602;
int DAT_800d15e4;

int CBruce_Trick_HoldTrick(unsigned char *s, int a);
int GetCharIndex(int c);

int Mess_TextHeightAboveBaseline(unsigned char *s, int a1) {
	int m;
	int v;
	int c;
	unsigned char *p;

	if (!DAT_800d1602)
		return CBruce_Trick_HoldTrick(s, a1);

	m = 0;
	p = s;

	while (*p) {
		c = GetCharIndex(*p);

		if ((unsigned)(c - 250) < 5)
			v = 0;
		else if (c == 255)
			v = 0;
		else
			v = *(int *)((char *)(DAT_800a6124[DAT_800d15e4].p) + c * 36 + 16);

		if (m < v)
			m = v;

		p++;
	}

	return (m * DAT_800a6110[DAT_800d15e4].h) >> 8;
}
