/* Vibrate__6CBruceiii (0x8002f8f0) */
#include "names.h"
typedef struct {
	char _0[0x870];
	int pad;
} CBruce;

struct S {
	int _[0x252];
	int v;
};

extern int GGame __attribute__((section(".data"))),
    GHorsePlayer __attribute__((section(".data")));

extern int GCareer[];
extern int GVInfo1[], GVInfo2[];

extern void Pad_ActuatorOn(unsigned char, unsigned short, unsigned char, unsigned char);

void Vibrate(CBruce *b, int a, int c, int d) {
	int p = b->pad;

	if (GGame == 7)
		p ^= GHorsePlayer;

	{
		int *q = GCareer;
		int *r = q + 0x252;

		r = r + p;

		if (*r == 0)
			return;
	}

	if (GVInfo1[0] == 2)
		return;

	if (GVInfo2[0] == 2)
		return;

	Pad_ActuatorOn(p, a, c, d);
}
