/* FUN_80025a88 (0x80025a88) flags=-fstructure-noalias */
#include "names.h"
typedef struct L {
	char pad[12];
	int f;
	char q[104];
} L;

typedef struct SP {
	char *a;
	char *b;
	int pad;
	int c;
	char pad2[0x40 - 0x10];
	char *s;
	char pad3[0x154 - 0x44];
} SP;

typedef struct CB {
	char p0[308];
	int m308;
	char p1[404 - 312];
	int m404;
	char *m408;
	char p2[468 - 412];
	struct CB *m468;
	struct CC *m472;
	char p3[744 - 476];
	int m744;
	char p4[2160 - 748];
	int m2160;
} CB;

typedef struct CC {
	char p0[1412];
	int m1412;
} CC;

extern L DAT_800a5398[];
extern SP DAT_800a44fc[];
extern int DAT_800a42f4[];
extern char DAT_800a8240[];
extern char DAT_800a8245[];
extern int DAT_800d1114;

int DAT_800d16a4;
int DAT_800d16d8;
int DAT_800d1780;
int DAT_800d179c;
CB *DAT_800d17c8;
CB *DAT_800d17cc;

extern int DAT_800d1de8;
extern int DAT_800d1e28;

void *__nw__5CItemUi(int);
CB *CBruce_ctor(void *);
CC *CCamera_ctor(void *, CB *, int);
void TrickTips_Init(void);
void CCamera_StartCompetitionIntro(CC *);
void CBruce_InitItem(CB *, char *);
void CBruce_GetStats(CB *, int);

void FUN_80025a88(void) {
	CB *pBruce;
	CC *pCam;
	CB *p2;
	CC *c2;

	pBruce = __nw__5CItemUi(3612);

	if (pBruce)
		pBruce = CBruce_ctor(pBruce);

	DAT_800d17c8 = pBruce;
	DAT_800d17cc = 0;
	pBruce->m2160 = 0;
	pCam = __nw__5CItemUi(1712);

	if (pCam)
		pCam = CCamera_ctor(pCam, pBruce, 0);

	pCam->m1412 = 1;
	TrickTips_Init();

	if (DAT_800a5398[DAT_800d1e28].f && DAT_800d16a4 == 1 && DAT_800a42f4[0] == 0 &&
	    DAT_800d1de8 == 0)
		CCamera_StartCompetitionIntro(pCam);

	if (DAT_800d16a4 != 7 || DAT_800d179c == 0)
		pBruce->m744 = DAT_800d1114;
	else
		pBruce->m744 = DAT_800d16d8;

	pBruce->m472 = pCam;

	if (DAT_800d1780 == 2 && DAT_800d16a4 != 7)
		CBruce_InitItem(pBruce, DAT_800a44fc[pBruce->m744].b);
	else
		CBruce_InitItem(pBruce, DAT_800a44fc[pBruce->m744].a);

	if (*DAT_800a44fc[pBruce->m744].s == 'R' || *DAT_800a44fc[pBruce->m744].s == 'r')
		pBruce->m308 |= 2;

	pBruce->m408 = DAT_800a8240;
	CBruce_GetStats(pBruce, 0);

	if (DAT_800a44fc[pBruce->m744].c == 16384)
		pBruce->m404 |= 4096;

	if (DAT_800d1780 == 2 && DAT_800d16a4 != 7) {
		p2 = __nw__5CItemUi(3612);

		if (p2)
			p2 = CBruce_ctor(p2);

		p2->m2160 = 1;
		c2 = __nw__5CItemUi(1712);

		if (c2)
			c2 = CCamera_ctor(c2, p2, 0);

		c2->m1412 = 1;
		p2->m744 = DAT_800d16d8;
		CBruce_InitItem(p2, DAT_800a44fc[DAT_800d16d8].b);

		if (*DAT_800a44fc[p2->m744].s == 'R' || *DAT_800a44fc[p2->m744].s == 'r')
			p2->m308 |= 2;

		pBruce->m468 = p2;
		p2->m468 = pBruce;
		p2->m472 = c2;
		DAT_800d17cc = p2;
		p2->m408 = DAT_800a8245;
		CBruce_GetStats(p2, 1);
	}
}
