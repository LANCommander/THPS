/* FUN_80084ebc (0x80084ebc) */
typedef struct { int a, b; } E;
typedef struct { short a; unsigned short n; unsigned short i; unsigned short m; char pad[20]; E v[1]; } P;
int DAT_800d21c0;
int DAT_800d21b8;
int DAT_800d21b4;
int DAT_800d2140;
int FUN_800860cc(E *, int);
int FUN_80085e98(E *, int);
void FUN_80086500(int, int);
void FUN_80086f40(E *, E *, int);
void FUN_80084ebc(P *p)
{
	int n = p->n;
	E *v = p->v;
	int r;
	if (DAT_800d21c0)
		r = FUN_800860cc(v, n);
	else
		r = FUN_80085e98(v, n);
	if (DAT_800d21b8)
		FUN_80086500(n, DAT_800d2140);
	v += n;
	if (!DAT_800d21b4 && !(r & 0xbf))
		FUN_80086f40(v + p->i, v, p->m);
}
