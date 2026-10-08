/* Video_SetHeader__FP10SVideoHeadi (0x80069394) */
#include "names.h"
typedef struct {
	int a, b;
} SVideoMark;

typedef struct {
	int state, f4, f8, fc;
	unsigned *p;
	unsigned buf;
	int n;
	int f1c;
	char pad[0x30];
	SVideoMark marks[14];
} SVideoInfo;

typedef struct {
	int f0;
	SVideoMark marks[5];
	unsigned short f2c, f2e, f30, f32, f34, f36;
} SVideoHead;

typedef struct CBruce {
	char pad[0x1c];
	struct CBruce *other;
	char pad2[0x2e8 - 0x20];
	unsigned short f2e8;
} CBruce;

extern SVideoInfo DAT_800bf318[];
extern CBruce *DAT_800d19a4;
extern unsigned short DAT_800d1780, DAT_800d1e28, DAT_800d16a4;

void Video_SetHeader(SVideoHead *h, int which) {
	SVideoInfo v;
	int i;
	CBruce *b, *o;

	{
		SVideoInfo *p;

		if (which)
			p = &DAT_800bf318[1];
		else
			p = &DAT_800bf318[0];

		v = *p;
	}

	h->f0 = v.f1c;

	for (i = 0; i < 5; i++)
		h->marks[i] = v.marks[i];

	{
		unsigned short t = DAT_800d1780;

		b = DAT_800d19a4;
		h->f2c = t;
	}

	o = b->other;

	switch (which) {
		case 0:
			h->f2e = b->f2e8;

			if (o)
				h->f30 = o->f2e8;

			break;
		case 1:
			h->f2e = o->f2e8;

			if (o)
				h->f30 = b->f2e8;

			break;
	}

	{
		unsigned short x = DAT_800d1e28, y = DAT_800d16a4;

		h->f36 = 0;
		h->f32 = x;
		h->f34 = y;
	}
}
