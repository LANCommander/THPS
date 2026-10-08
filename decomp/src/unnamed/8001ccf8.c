/* FUN_8001ccf8 (0x8001ccf8) */
#include "names.h"
extern char *DAT_800d1f84;
extern char DAT_8009e4ec[];
extern char DAT_8009e4f8[];
extern char DAT_8009e504[];
extern char DAT_8009e510[];
extern char DAT_8009e520[];
extern char DAT_8009e52c[];

typedef struct {
	char *a;
	char *b;
	char pad[11];
	unsigned char c13;
	signed char c14;
	char pad2[319];
} E;

extern E DAT_800a44fc[];

typedef struct {
	int p0, p1, f8, fc;
	char pad[104];
} T;

extern T DAT_800a5398[];

typedef struct {
	char pad[11];
	char f;
	char pad2[52];
} B;

extern B DAT_800bf7a8[];
extern int DAT_800d1114;
extern char DAT_800d14e4[];
extern char DAT_800d14ec[];
extern int DAT_800d16a4;
extern int DAT_800d16d8;
extern int DAT_800d1724;
extern int DAT_800d1780;
extern int DAT_800d184c;
extern int DAT_800d1850;
extern int DAT_800d1854;
extern int DAT_800d1858;
extern char DAT_800d1a15;
extern char DAT_800d1a16;
extern int DAT_800d1cf0;
extern int DAT_800d1e28;
extern int DAT_800d2120;
extern int DAT_800d2130;

void Bit_Init(void);
void FUN_80025a88(void);
void Trig_ExecuteRestart(void);
void Trig_InitialParseTRGFile(char *);
void FUN_8004b09c(char *);
void FUN_8004b0e4(int);
void FUN_8004b180(void);
void FUN_8004bb5c(void);
void FUN_8004c740(int);
void FUN_8005dc8c(void);
int __6SpritePciii(int, char *, int, int, int);
void FUN_8006c4c4(void);
int Spool_PSX(char *, int, int);
void Font_Init(void);
int Front_FindLevel(char *);
void Front_SaveGameState(void);
void Redbook_InitialRand(int);
void SFX_SetReverbType(int);
void Spool_ClearAllPSXs(void);
void Spool_Sync(void);
void Trig_SetRestart(char *);
int __nw__6CClassUi(int);

void FUN_8001ccf8(char *p) {
	int a, b, s2, t1, t2, u1, u2, i1;
	char *bt, *bt2;
	E *q;
	char *bp, *bp2;
	B *tb, *tb2;

	DAT_800d1f84 = p + 4;
	Redbook_InitialRand(0x12a6cc58);
	FUN_8004c740(2000);
	FUN_8004b09c(DAT_8009e4ec);
	FUN_8004b0e4(DAT_800a5398[DAT_800d1e28].f8);
	SFX_SetReverbType(0);

	a = __nw__6CClassUi(24);

	if (a)
		a = __6SpritePciii(a, DAT_8009e4f8, 1, 256, 256);

	DAT_800d184c = a;
	a = __nw__6CClassUi(24);

	if (a)
		a = __6SpritePciii(a, DAT_8009e504, 1, 256, 256);

	DAT_800d1850 = a;
	a = __nw__6CClassUi(24);

	if (a)
		a = __6SpritePciii(a, DAT_8009e510, 1, 256, 256);

	DAT_800d1854 = a;
	b = __nw__6CClassUi(24);

	if (b)
		b = __6SpritePciii(b, DAT_8009e520, 1, 64, 256);

	DAT_800d1858 = b;
	i1 = Spool_PSX(DAT_800d14e4, 0, 0);
	bt = (char *)DAT_800bf7a8;
	tb = (B *)(bt + i1 * 64);
	tb->f = 1;
	s2 = Spool_PSX(DAT_800d14ec, 0, 0);
	tb2 = (B *)(bt + s2 * 64);
	tb2->f = 1;
	DAT_800d1a15 = s2;
	Spool_Sync();
	FUN_8004c740(4);
	FUN_8006c4c4();
	Font_Init();
	Bit_Init();
	Spool_ClearAllPSXs();

	if (DAT_800a5398[DAT_800d1e28].fc && DAT_800d16a4 == 1)
		s2 = Spool_PSX(DAT_8009e52c, 0, 0);

	DAT_800d1a16 = s2;

	if (DAT_800d1724) {
		bp = (char *)DAT_800a44fc;
		q = (E *)(bp + DAT_800d1114 * 340);
		t1 = q->c13;
		t2 = q->c14;
		DAT_800d2120 = t1;
		DAT_800d2130 = t2;
	}

	if (DAT_800d1780 == 2 && DAT_800d16a4 != 7)
		Spool_PSX(DAT_800a44fc[DAT_800d1114].b, 0, 0);
	else
		Spool_PSX(DAT_800a44fc[DAT_800d1114].a, 0, 0);

	Spool_Sync();

	DAT_800d2120 = -1;

	if (DAT_800d1780 == 2) {
		if (DAT_800d1724) {
			bp2 = (char *)DAT_800a44fc;
			q = (E *)(bp2 + DAT_800d16d8 * 340);
			u1 = q->c14;
			u2 = q->c13;
			DAT_800d2130 = u1;
			DAT_800d2120 = u2;
		}

		if (DAT_800d16a4 != 7)
			Spool_PSX(DAT_800a44fc[DAT_800d16d8].b, 0, 0);
		else
			Spool_PSX(DAT_800a44fc[DAT_800d16d8].a, 0, 0);

		Spool_Sync();

		DAT_800d2120 = -1;
	}

	if (Front_FindLevel(DAT_800d1f84)) {
		FUN_8004bb5c();
		FUN_8004b180();
	}

	FUN_8004c740(2000);
	Trig_InitialParseTRGFile(DAT_800d1f84);
	FUN_8005dc8c();
	FUN_8004c740(4);

	if (DAT_800d1cf0 == 0) {
		FUN_80025a88();

		if (p[13])
			Trig_SetRestart(p + 13);

		Trig_ExecuteRestart();
		Front_SaveGameState();
	}
}
