/* FUN_80043f70 (0x80043f70) */
typedef struct {
	char p0[0x144];
	short f144;
	unsigned short f146;
	char f148;
	signed char f149;
	signed char f14a;
	signed char f14b;
	unsigned short f14c;
	unsigned char f14e;
	char f14f;
	int f150;
} O;

extern int DAT_800d1774;

void FUN_80043f70(O *o) {
	int v, a, c, d, s;
	unsigned char ub;

	if (o->f148 == 0) {
		c = o->f149;

		if ((c == 1 && (a = (unsigned char)o->f14a, o->f144 >= o->f14a)) ||
		    (c == -1 && (a = (unsigned char)o->f14a, o->f144 <= o->f14a))) {
			if ((ub = o->f14b, o->f14b > 0)) {
				o->f14a = ub;
				o->f14b = a;
				o->f149 = -(unsigned char)o->f149;
			} else
				o->f14f = 1;
		}
	}

	v = (o->f144 << 16) | o->f14c;
	d = o->f149;
	a = (o->f150 * DAT_800d1774) >> 8;

	if (d == 1)
		v += a;

	if (d == -1)
		v -= a;

	s = v >> 16;
	o->f144 = s;
	o->f14c = v;

	switch ((unsigned char)o->f148) {
		case 0:
			if ((d == 1 && !(s < o->f14a)) || (d == -1 && !(o->f14a < s)))
				o->f144 = (signed char)(unsigned char)o->f14a;

			break;
		case 1:
			if (s >= o->f14e)
				o->f144 = 0;

			if (o->f144 < 0)
				o->f144 = o->f14e - 1;

			break;
	}
}
