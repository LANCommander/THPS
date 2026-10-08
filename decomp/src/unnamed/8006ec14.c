/* Spool_Init__Fv (0x8006ec14) */
typedef struct {
	char a0;
	char pad0[9];
	char a10, a11;
	char pad1[4];
	int f16, f20, f24, f28, f32, f36, f40, f44;
	char pad2[3];
	char a51, a52;
	char pad3[11];
} T;

extern T DAT_800bf7a8[];
extern char DAT_800bf661[][17];
extern int DAT_800c01a8[];

int DAT_800d1ef4;
int DAT_800d1ef8;
int DAT_800d1efc;
int DAT_800d1ed0;
int DAT_800d1ed4;
int DAT_800d1ed8;
int DAT_800d1edc;
int DAT_800d1eec;
int DAT_800d1ef0;

void Spool_Init__Fv(void) {
	int i;

	for (i = 0; i < 20; i++)
		DAT_800bf661[i][0] = 0;

	DAT_800d1ef4 = 0;
	DAT_800d1ef8 = 0;

	for (i = 0; i < 40; i++) {
		DAT_800bf7a8[i].a0 = 0;
		DAT_800bf7a8[i].a11 = 0;
		DAT_800bf7a8[i].a10 = 0;
		DAT_800bf7a8[i].f16 = 0;
		DAT_800bf7a8[i].f20 = 0;
		DAT_800bf7a8[i].f24 = 0;
		DAT_800bf7a8[i].f28 = 0;
		DAT_800bf7a8[i].f44 = 0;
		DAT_800bf7a8[i].f40 = 0;
		DAT_800bf7a8[i].f32 = 0;
		DAT_800bf7a8[i].a51 = 0;
		DAT_800bf7a8[i].a52 = 0;
	}

	for (i = 0; i < 512; i++)
		DAT_800c01a8[i] = 0;

	DAT_800d1efc = 0;
	DAT_800d1ed0 = -1;
	DAT_800d1ed4 = -1;
	DAT_800d1ed8 = 0;
	DAT_800d1edc = 0;
	DAT_800d1eec = 0;
	DAT_800d1ef0 = 0;
}
