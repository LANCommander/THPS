/* __9PadBufferi (0x80063e34) */
#include "names.h"
typedef struct {
	char pad[128];
	char a;
	char p1[15];
	char b;
	char p2[15];
	char c;
	char p3[15];
	char d;
	char rest[364 - 177];
} S;

typedef struct {
	char *f0;
	int f4;
	int f8;
	char pad[256];
	int f268;
	int f272;
	int pad2;
	int f280;
} P;

extern S DAT_800c0a48[];
extern char DAT_800a2170[];

int DAT_800d1d9c;

P *PadBuffer_ctor(P *p, int a1) {
	int fl = DAT_800d1d9c;
	S *t;

	p->f0 = DAT_800a2170;
	p->f4 = 0;
	p->f8 = 0;
	p->f272 = 0;
	p->f268 = 0;
	p->f280 = a1;

	if (fl)
		p->f280 = 0;

	if ((unsigned)p->f280 < 2) {
		t = DAT_800c0a48;
		t[p->f280].a = 0;
		t[p->f280].b = 0;
		t[p->f280].c = 0;
		t[p->f280].d = 0;
	} else {
		DAT_800c0a48[0].a = 0;
		DAT_800c0a48[0].b = 0;
		DAT_800c0a48[0].c = 0;
		DAT_800c0a48[0].d = 0;
		DAT_800c0a48[1].a = 0;
		DAT_800c0a48[1].b = 0;
		DAT_800c0a48[1].c = 0;
		DAT_800c0a48[1].d = 0;
	}

	return p;
}
