/* FUN_80084d18 (0x80084d18) */
typedef struct { int a, b; } E;
typedef struct { short a; unsigned short n; unsigned short i; unsigned short m; char pad[20]; E v[1]; } P;
short DAT_800d2144;
short DAT_800d2146;
short DAT_800d2148;
int DAT_800d21b8;
int DAT_800d2140;
int FUN_80085d28(E *, int);
void FUN_80086500(int, int);
void FUN_8009736c(int, int, int);
void FUN_80086f40(E *, E *, int);
void FUN_80084d18(P *p)
{
	E *v = p->v;
	int n = p->n;
	int r = FUN_80085d28(v, n);
	E *w;
	if (DAT_800d21b8)
		FUN_80086500(n, DAT_800d2140);
	v += n;
	if (!(r & 0xbf)) {
		n = p->m;
		w = v + p->i;
		FUN_8009736c(DAT_800d2144, DAT_800d2146, DAT_800d2148);
		FUN_80086f40(w, v, n);
	}
}
