/* FUN_8005de7c (0x8005de7c) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

typedef struct {
	char a, b, c, d, e[10];
} R;

extern R DAT_800a684c[];

int DAT_800d1d24;

extern char DAT_800a1bd4[], DAT_800a1be0[], DAT_800a1bec[], DAT_800a1bf8[];

struct O *DAT_800d2358;
struct O *DAT_800d235c;

extern void Pack_DefragmentFully__Fv(void);
extern void FUN_8005c97c(int);
extern void FUN_8005ca64(void);
extern int FUN_8005ca3c(char *);
extern void FUN_80061714(int);
extern void Mess_LoadFont__FPcT0iii(char *, int, int, int, int);
extern void Mess_SetFontScale__FUi(unsigned);
extern struct O *__nw__6CClassUi(unsigned);
extern struct O *__6SpritePciii(struct O *, char *, int, int, int);
extern void FUN_8005c8dc(int);
extern int FUN_8005e754(int);

int FUN_8005de7c(int a) {
	int i, j, r;
	struct O *o, *p, *q;

	Pack_DefragmentFully__Fv();
	FUN_8005c97c(0);
	FUN_8005ca64();

	if (DAT_800d1d24) {
		for (i = 0; i < 11; i++) {
			DAT_800a684c[i].a = 0;
			DAT_800a684c[i].d = 0;
			DAT_800a684c[i].c = 0;
			DAT_800a684c[i].b = 0;

			for (j = 0; j < 10; j++) {
				DAT_800a684c[i].e[j] = 255;
				DAT_800a684c[i].a += 5;
				DAT_800a684c[i].d += 1;
				DAT_800a684c[i].c += 1;
				DAT_800a684c[i].b += 1;
			}
		}
	}

	FUN_80061714(FUN_8005ca3c(DAT_800a1bd4));
	Mess_LoadFont__FPcT0iii(DAT_800a1be0, FUN_8005ca3c(DAT_800a1be0), -1, -1, -1);
	Mess_SetFontScale__FUi(200);

	o = __nw__6CClassUi(24);

	if (o)
		o = __6SpritePciii(o, DAT_800a1bec, 1, 32, 128);

	DAT_800d2358 = o;
	p = __nw__6CClassUi(24);

	if (p)
		p = __6SpritePciii(p, DAT_800a1bf8, 1, 32, 128);

	DAT_800d235c = p;
	FUN_8005c8dc(1);

	r = FUN_8005e754(a);
	q = DAT_800d2358;

	if (q)
		q->vt->fn((char *)q + q->vt->off, 3);

	q = DAT_800d235c;

	if (q)
		q->vt->fn((char *)q + q->vt->off, 3);

	return r;
}
