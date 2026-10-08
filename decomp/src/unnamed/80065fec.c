/* FUN_80065fec (0x80065fec) */
typedef struct {
	void *a;
	int p4[5];
	int f18;
	int sz;
	int f20;
} E;

typedef struct {
	int p0[2];
	int n;
	int pc;
	E e[1];
} S;

extern int Mem_NewTop__FUi(int a);
extern int Mem_NewX__FUiii(int a, int b, int c);
extern int Mem_Delete__FPv(void *a);
extern int Mem_Copy__FPvT0i(void *a, void *b, int c);

void FUN_80065fec(S *s) {
	int tmp[32];
	int i;

	for (i = 0; i < s->n; i++) {
		if (s->e[i].f20 && !s->e[i].f18) {
			tmp[i] = Mem_NewTop__FUi(s->e[i].sz);
			Mem_Copy__FPvT0i((void *)tmp[i], s->e[i].a, s->e[i].sz);
			Mem_Delete__FPv(s->e[i].a);
		}
	}

	for (i = 0; i < s->n; i++) {
		if (s->e[i].f20 && !s->e[i].f18) {
			s->e[i].a = (void *)Mem_NewX__FUiii(s->e[i].sz, 1, 1);
			Mem_Copy__FPvT0i(s->e[i].a, (void *)tmp[i], s->e[i].sz);
			Mem_Delete__FPv((void *)tmp[i]);
		}
	}
}
