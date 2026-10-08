/* __10CGPolyLinei (0x8002725c) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	V v;
	int w;
} E;

extern char DAT_8009f658[];
extern V DAT_800a824c;
extern char DAT_800d18f8[8];

void __4CBit(char *p);
char *Mem_NewX__FUiii(int a, int b, int c);
void AttachTo__4CBitPv(char *p, char *q);

char *__10CGPolyLinei(char *p, int n) {
	int i;

	__4CBit(p);

	*(char **)(p + 68) = DAT_8009f658;
	*(char **)(p + 76) = Mem_NewX__FUiii(n << 4, 0, 1);

	for (i = 0; i < n; i++) {
		(*(E **)(p + 76))[i].w = 0x50ffffff;
		(*(E **)(p + 76))[i].v = DAT_800a824c;
	}

	*(int *)(p + 72) = n;
	AttachTo__4CBitPv(p, DAT_800d18f8);

	p[92] = 255;
	p[93] = 255;
	p[94] = 255;
	p[95] = 80;
	return p;
}
