/* FUN_80084dc0 (0x80084dc0) */
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

short DAT_800d2144;
short DAT_800d2146;
short DAT_800d2148;

int FUN_80089790(E *, int, int);
void FUN_8009736c(int, int, int);
void FUN_800898ac(E *, E *, int);

void FUN_80084dc0(P *p, int c) {
	E *v = p->v;
	int n = p->n;
	int r = FUN_80089790(v, n, c);
	E *w;

	v += n;

	if (!(r & 0x6000e000)) {
		n = p->m;
		w = v + p->i;
		FUN_8009736c(DAT_800d2144, DAT_800d2146, DAT_800d2148);
		FUN_800898ac(w, v, n);
	}
}
