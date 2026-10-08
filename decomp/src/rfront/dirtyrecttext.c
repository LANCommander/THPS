/* Front_DirtyRectText__FiiPCc (0x80011324) */
typedef struct {
	char *ptr;
	const char *str;
	short x, y;
	int pad;
	int state;
} T;

extern T DAT_800a4434[];

int DAT_800d1118;

void FUN_8001e114(int, int, const char *, int, int, int, int);
int FUN_8001da44(const char *);
int Mess_TextHeight__FPCc(const char *);
char *__nw__5CItemUi(unsigned);
char *FUN_80063928(char *, int, int, int, int, int, int, int);

void Front_DirtyRectText__FiiPCc(int x, int y, const char *s) {
	int i, w, h, nx;
	T *e;
	char *p;

	for (i = 0; i < DAT_800d1118; i++) {
		if (DAT_800a4434[i].str == s) {
			FUN_8001e114(x, y, s, 0, 0, 256, 0);
			return;
		}
	}

	DAT_800a4434[DAT_800d1118].str = s;
	w = FUN_8001da44(s);
	h = Mess_TextHeight__FPCc(s);
	nx = x - (w >> 1);
	w += 4;
	e = &DAT_800a4434[DAT_800d1118];
	e->x = nx;
	e->y = y - h;
	h += 4;
	p = __nw__5CItemUi(24);

	if (p)
		p = FUN_80063928(p, nx, DAT_800a4434[DAT_800d1118].y, w, h, 1, 32, 128);

	e->ptr = p;
	DAT_800a4434[DAT_800d1118].state = 2;
	DAT_800d1118++;
}
