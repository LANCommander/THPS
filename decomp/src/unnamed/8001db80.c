/* FUN_8001db80 (0x8001db80) */
typedef struct {
	int **p;
	char pad[32];
} A;

typedef struct {
	char pad[20];
	int *p;
	char pad2[2];
	unsigned short h;
	char pad3[8];
} B;

extern A DAT_800a6124[];
extern B DAT_800a6110[];

unsigned char DAT_800d1602;
int DAT_800d15e4;

int FUN_8001d548(unsigned char *s);
int FUN_8001ddfc(int c);

int FUN_8001db80(unsigned char *s) {
	int m;
	int v;
	int c;
	unsigned char *p;

	if (!DAT_800d1602)
		return FUN_8001d548(s);

	m = 0;
	p = s;

	while (*p) {
		c = FUN_8001ddfc(*p);

		if ((unsigned)(c - 250) < 5)
			v = 0;
		else if (c == 255)
			v = 0;
		else
			v = *(int *)((char *)(DAT_800a6124[DAT_800d15e4].p) + c * 36 + 4) -
			    *(int *)((char *)(DAT_800a6124[DAT_800d15e4].p) + c * 36 + 16);

		if (m < v)
			m = v;

		p++;
	}

	return (m * DAT_800a6110[DAT_800d15e4].h) >> 8;
}
