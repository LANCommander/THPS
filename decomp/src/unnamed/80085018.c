/* FUN_80085018 (0x80085018) */
typedef struct {
	int a, b;
} E;

typedef struct {
	short a;
	unsigned short n;
	unsigned short i;
	unsigned short m;
	char pad[20];
	E v[1];
} P;

short FarColor;
short FarColor_2;
short FarColor_4;
int TestTheWater;
int WaterClipValue;

int FUN_80086d2c(E *, int, int);
void FUN_80086500(int, int);
void FUN_8009736c(int, int, int);
void FUN_80086f40(E *, E *, int);

void FUN_80085018(P *p, int c) {
	E *v = p->v;
	int n = p->n;
	int r = FUN_80086d2c(v, n, c);
	E *w;

	if (TestTheWater)
		FUN_80086500(n, WaterClipValue);

	v += n;

	if (!(r & 0xbf)) {
		n = p->m;
		w = v + p->i;
		FUN_8009736c(FarColor, FarColor_2, FarColor_4);
		FUN_80086f40(w, v, n);
	}
}
