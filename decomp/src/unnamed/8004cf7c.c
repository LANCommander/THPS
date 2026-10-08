/* FUN_8004cf7c (0x8004cf7c) */
typedef struct B {
	struct B *next;
	unsigned flags : 4;
	unsigned len : 28;
} B;

typedef struct {
	B *a;
	unsigned b;
} R;

extern R DAT_800be09c[];

int DAT_800d1b5c[2];
int DAT_800d1b64[2];
unsigned DAT_800d1b54;

void AddToFreeList__FP12SBlockHeaderi(B *b, int i);

void FUN_8004cf7c(void) {
	int i;

	for (i = 0; i < 2; i++) {
		DAT_800d1b64[i] = 0;
		DAT_800d1b5c[i] = 0;

		{
			B *b = DAT_800be09c[i].a;

			b->len = DAT_800be09c[i].b - (unsigned)b - 8;
			AddToFreeList__FP12SBlockHeaderi(b, i);
		}
	}

	DAT_800d1b54 = (98 * (DAT_800be09c[1].b - (unsigned)DAT_800be09c[1].a)) / 100;
}
