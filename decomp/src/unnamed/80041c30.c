/* FUN_80041c30 (0x80041c30) */
typedef struct {
	char pad[16];
	unsigned char a, b, c;
	char q[340 - 19];
} T;

typedef struct {
	char pad[404];
	int flags;
	char q[744 - 408];
	int idx;
} P;

extern T DAT_800a44fc[];

void FUN_80041c30(P *p) {
	T *base = DAT_800a44fc;
	T *t = &base[p->idx];

	p->flags |= (1 << t->a) | (1 << t->b) | (1 << t->c);
}
