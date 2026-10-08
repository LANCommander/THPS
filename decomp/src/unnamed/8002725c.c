/* FUN_8002725c (0x8002725c) */
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

void FUN_80027e44(char *p);
char *FUN_8004d068(int a, int b, int c);
void AttachTo__4CBitPv(char *p, char *q);

char *FUN_8002725c(char *p, int n) {
	int i;

	FUN_80027e44(p);

	*(char **)(p + 68) = DAT_8009f658;
	*(char **)(p + 76) = FUN_8004d068(n << 4, 0, 1);

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
