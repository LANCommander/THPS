/* Mess_Display__Fv (0x8001d764) */
typedef struct {
	unsigned short us0;
	unsigned char b2, b3;
	unsigned short us4, us6;
	unsigned char b8, b9, b10, b11, b12, b13;
	unsigned short us14, us16;
	short s18, s20, s22, s24;
	unsigned char b26, _27;
	unsigned short us28;
} Anim;

typedef struct Node {
	char *text;
	unsigned short t;
	short _6;
	short s8, s10;
	int f12;
	Anim *anim;
	struct Node *next;
} Node;

Node *DAT_800d15ec;
char DAT_800d15f0;
int DAT_800d15f4;
unsigned short DAT_800d15f8;

extern volatile unsigned DAT_800d1a24;

void Mess_SetScale__Fi(int);
void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_DrawPanelText__FiiPCciUii(int, int, const char *, int, unsigned, int);

void Mess_Display__Fv(void) {
	Node *head;
	Node *n;
	Anim *a;
	int cnt, off, x, y, w, v, d;
	unsigned char cr, cg, cb;
	int sc, q4;
	unsigned short Dur;

	head = n = DAT_800d15ec;
	cnt = 0;

	for (; n; n = n->next)
		if (n->f12)
			cnt++;

	off = (cnt - 1) << 4;

	for (n = head; n; n = n->next) {
		a = n->anim;

		if (a->b26 && !((n->t / a->b26) & 1))
			continue;

		Dur = a->us0;
		DAT_800d15f0 = a->b3;
		DAT_800d15f8 = ((a->us6 - a->us4) * n->t) / Dur + a->us4;
		Mess_SetScale__Fi(DAT_800d15f8);

		cr = a->b8 + ((a->b11 - a->b8) * n->t) / Dur;
		cg = a->b9 + ((a->b12 - a->b9) * n->t) / Dur;
		cb = a->b10 + ((a->b13 - a->b10) * n->t) / Dur;
		v = (cb << 16) | (cg << 8) | cr;
		DAT_800d15f4 = v;

		if (a->b2)
			DAT_800d15f4 |= 0x2e000000;
		else
			DAT_800d15f4 |= 0x2c000000;

		if (a->us28)
			Mess_SetRGB__FUcUcUci(((DAT_800d1a24 % 20) * 12) & 252, 100, 100, 0);

		x = a->s20 + ((a->s24 - a->s20) * n->t) / Dur + n->s10;
		y = a->s18 + ((a->s22 - a->s18) * n->t) / Dur + n->s8;

		if (n->f12) {
			x += off;
			off -= 32;
		}

		w = a->us14 + ((a->us16 - a->us14) * n->t) / Dur;
		Mess_DrawPanelText__FiiPCciUii(y, x, n->text, w, 0, 256);
	}
}
