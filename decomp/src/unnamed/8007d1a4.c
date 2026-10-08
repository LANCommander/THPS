/* __6CamPos (0x8007d1a4) */
extern char DAT_800a35a4[];
extern char DAT_800a35b4[];

struct X {
	char *vt;
	int a, b, c, d;
};

char *__6CamPos(char *p) {
	struct X *x = (struct X *)(p + 28);
	struct X *y = (struct X *)(p + 68);
	struct X *z = (struct X *)(p + 120);

	*(char **)p = DAT_800a35a4;
	x->vt = DAT_800a35b4;
	x->a = 0;
	x->b = 0;
	x->c = 0;
	x->d = 4096;
	y->vt = DAT_800a35b4;
	y->a = 0;
	y->b = 0;
	y->c = 0;
	y->d = 4096;
	z->vt = DAT_800a35b4;
	z->a = 0;
	z->b = 0;
	z->c = 0;
	z->d = 4096;
	return p;
}
