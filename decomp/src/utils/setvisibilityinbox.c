/* Utils_SetVisibilityInBox__FRC7CVectorT0bT2 (0x80048484) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct O1 {
	unsigned short f0;
	char p0[0x1b - 2];
	unsigned char f1b;
	int pad;
} O1;

typedef struct A {
	unsigned short f0;
	short p;
	int x, y, z;
	char p1[0x1b - 0x10];
	unsigned char f1b;
	struct A *next;
} A;

typedef struct {
	char p[10];
	unsigned char fa;
	char q[53];
} TE;

typedef struct B {
	int p;
	struct B *next;
	char p0[0x18 - 8];
	int x;
	int y;
	int z;
	char p1[0x43 - 0x24];
	unsigned char f43;
	char p2[0x56 - 0x44];
	unsigned char f56;
} B;

extern TE DAT_800bf7a8[];
extern A *DAT_800d1eec;
extern A *DAT_800d1618;
extern A *DAT_800d19b4;
extern A *DAT_800d19b0;
extern B *DAT_800d18cc;
extern int DAT_800d199c, DAT_800d1780, DAT_800d16a4, DAT_800d19a4;

#define INSIDE(v, w, u)  (v >= t8 && t5 >= v && w >= t6 && t3 >= w && u >= t7 && t4 >= u)
#define OUTSIDE(v, w, u) ((v < t8 || t5 < v) && (w < t6 || t3 < w) && (u < t7 || t4 < u))
#define SET(o)           o->f0 = (o->f0 & t2) | t1

void Utils_SetVisibilityInBox(V *a, V *b, int arg2, int arg3) {
	int t8 = a->x, t7 = a->y, t6 = a->z, t5 = b->x, t4 = b->y, t3 = b->z;
	int t1, t2;
	A *o;
	B *q;

	if (DAT_800d199c == 0 || DAT_800d1780 == 1 || DAT_800d16a4 == 7)
		t1 = 0x41;
	else {
		t1 = 1;

		if (DAT_800d199c == DAT_800d19a4)
			t1 = 0x40;
	}

	t2 = ~t1;

	if (arg2)
		t1 = 0;
	else
		t2 = -1;

	o = DAT_800d1eec;

	if (o) {
		do {
			TE *e = &DAT_800bf7a8[o->f1b];

			if (e->fa != 0) {
				int x = o->x, y = o->y, z = o->z;

				if (arg3) {
					if (INSIDE(x, z, y))
						SET(o);
				} else {
					if (OUTSIDE(x, z, y))
						SET(o);
				}
			}

			o = o->next;
		} while (o);
	}

	o = DAT_800d1618;

	if (o) {
		do {
			if (arg3) {
				if (INSIDE(o->x, o->z, o->y))
					SET(o);
			} else {
				if (OUTSIDE(o->x, o->z, o->y))
					SET(o);
			}

			o = o->next;
		} while (o);
	}

	o = DAT_800d19b4;

	if (o) {
		do {
			if (arg3) {
				if (INSIDE(o->x, o->z, o->y))
					SET(o);
			} else {
				if (OUTSIDE(o->x, o->z, o->y))
					SET(o);
			}

			o = o->next;
		} while (o);
	}

	o = DAT_800d19b0;

	if (o) {
		do {
			if (arg3) {
				if (INSIDE(o->x, o->z, o->y))
					SET(o);
			} else {
				if (OUTSIDE(o->x, o->z, o->y))
					SET(o);
			}

			o = o->next;
		} while (o);
	}

	q = DAT_800d18cc;

	if (q) {
		do {
			if (q->f43 == 2) {
				if (arg3) {
					if (INSIDE(q->x, q->z, q->y)) {
						if (arg2)
							q->f56 = 1;
						else if (DAT_800d1780 == 1)
							q->f56 = 0;
					}
				} else {
					if (OUTSIDE(q->x, q->z, q->y)) {
						if (arg2)
							q->f56 = 1;
						else if (DAT_800d1780 == 1)
							q->f56 = 0;
					}
				}
			}

			q = q->next;
		} while (q);
	}
}
