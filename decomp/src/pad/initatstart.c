/* Pad_InitAtStart__Fv (0x80070878) */
typedef struct {
	char c[0x10];
} SControl;

typedef struct {
	SControl a, b, c, d;
	char _40[0x15c - 0x40];
	SControl *pa, *pc, *pb, *pd;
} Pad;

extern Pad DAT_800c0a48[];
extern char DAT_800c0d20[];

int DAT_800d1f68, DAT_800d1f74;

extern void Pad_ClearAll__Fv(void);
extern void FUN_80096304(char *, char *);
extern void FUN_80096050(void);
extern void FUN_800241d4(void);

void Pad_InitAtStart(void) {
	int i;

	for (i = 0; i < 2; i++) {
		DAT_800c0a48[i].pa = &DAT_800c0a48[i].a;
		DAT_800c0a48[i].pb = &DAT_800c0a48[i].c;
		DAT_800c0a48[i].pc = &DAT_800c0a48[i].b;
		DAT_800c0a48[i].pd = &DAT_800c0a48[i].d;
	}

	Pad_ClearAll__Fv();
	FUN_80096304(DAT_800c0d20, DAT_800c0d20 + 34);
	FUN_80096050();

	DAT_800d1f68 = 0;
	FUN_800241d4();

	DAT_800d1f74 = 1;
}
