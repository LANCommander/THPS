/* FUN_80066aa8 (0x80066aa8) */
typedef struct {
	int a, b, c, d, e;
} S;

extern int DAT_800d1a60;
extern int DAT_800d1a64;

S *DAT_800d2398[2];
int DAT_800d23a0[2];
char *DAT_800d23b0[2];
char *DAT_800d23b8[2];
int DAT_800d23a8;
int DAT_800d23ac;

S *FUN_8004982c(int a, int b, int c, char *d, char *e, int f, int g, int h);
S *FUN_8004d068(int a, int b, int c);

void FUN_80066aa8(void) {
	int i;
	S *s;

	for (i = 0; i < 2; i++) {
		s = FUN_8004982c(-1, 160, 256, (char *)&DAT_800d23b0[i], (char *)&DAT_800d23b8[i], 16, 0,
		                 0);
		DAT_800d2398[i] = FUN_8004d068(20, 1, 1);
		*DAT_800d2398[i] = *s;
		DAT_800d2398[i]->c = 0;
		DAT_800d23a0[i] = 0;
	}

	DAT_800d23a8 = DAT_800d1a60;
	DAT_800d23ac = DAT_800d1a64;
}
