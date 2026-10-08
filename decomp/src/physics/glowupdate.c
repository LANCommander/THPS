/* GlowUpdate__6CBruce (0x800424b4) */
typedef struct {
	char _0[0xb4];
	unsigned c;
	short s0;
	short s1;
	char _bc[0x874 - 0xbc];
	unsigned char cur[3];
	unsigned char tgt[3];
	unsigned char spd;
	unsigned char spd2;
} CBruce;

int GlowTowards__Fiii(int, int, int);

void GlowUpdate__6CBruce(CBruce *t) {
	t->cur[0] = GlowTowards__Fiii(t->cur[0], t->tgt[0], t->spd);
	t->cur[1] = GlowTowards__Fiii(t->cur[1], t->tgt[1], t->spd);
	t->cur[2] = GlowTowards__Fiii(t->cur[2], t->tgt[2], t->spd);

	if (t->cur[0] == t->tgt[0] &&
	    ((*(unsigned *)t->cur >> 8) & 0xffff) == *(unsigned short *)&t->tgt[1]) {
		if (t->spd2) {
			t->tgt[0] = 0;
			t->tgt[1] = 0;
			t->tgt[2] = 0;
			t->spd = t->spd2;
			t->spd2 = 0;
		}
	}

	if ((t->cur[0] | t->cur[1] | t->cur[2]) & 255) {
		t->s0 = 0x2000;
		t->s1 = 10;
		t->c = 0x2000000 | t->cur[0] | (t->cur[1] << 8) | (t->cur[2] << 16);
	} else {
		t->c = 0;
	}
}
