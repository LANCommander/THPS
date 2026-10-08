/* FUN_8002fe9c (0x8002fe9c) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	char p0[0x150];
	int f150;
	char p00[0x19c - 0x154];
	int f19c;
	char p1[0x218 - 0x1a0];
	int f218;
	char p2[0x24c - 0x21c];
	int f24c;
	char p3[0x358 - 0x250];
	int f358, f35c;
	char p4[0x6c - 0x360 + 0x360 - 0x6c];
} Q;

typedef struct {
	char p0[0x150];
	int f150;
	char p00[0x19c - 0x154];
	int f19c;
	char p1[0x218 - 0x1a0];
	int f218;
	char p2[0x24c - 0x21c];
	int f24c;
	char p3[0x358 - 0x250];
	int f358;
	int f35c;
	char p4[0x6dc - 0x360];
	int f6dc;
	int f6e0;
	char p5[0x71c - 0x6e4];
	int f71c;
	int f720;
	int f724;
	char p6[0x744 - 0x728];
	int f744;
	int f748;
} B;

typedef struct {
	char p[0xc];
	int fc;
	char q[0x154 - 0x10];
} E;

extern E DAT_800a44fc[];

void FUN_8002f774(void);
void FUN_8002f980(B *, int, int);
void FUN_8002fd80(B *, int, int, int, int);
void FUN_8002fe50(B *);
void BoardOff__6CBruce(B *);
void FUN_800429d0(B *);
void FUN_8004b250(int, int, int);
int Mips_CVecDotProd__FP7CVectorT0(void *, void *);
int FUN_8008b5dc(int);
int Redbook_Rnd__Fi(int);

void FUN_8002fe9c(B *p, int a) {
	p->f19c = a;
	p->f724 = 0;
	p->f218++;
	FUN_8002f774();

	p->f71c = 0;
	p->f358 = 1;
	p->f744 = 0;
	p->f748 = 0;
	FUN_8002fe50(p);

	p->f35c = 0;
	p->f6e0 = 0;
	FUN_8002f980(p, 1, 0x412);
	BoardOff__6CBruce(p);

	p->f150 = 0x10000;
	FUN_8002fd80(p, 0x36, 0, 0x1d, 0x416);

	if (0x2d000 < (FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0((char *)p + 0x6c, (char *)p + 0x6c)) << 6))
		p->f24c = 1;
	else
		p->f24c = 6;

	FUN_800429d0(p);

	if (DAT_800a44fc[*(int *)((char *)p + 0x2e8)].fc == 0x9000 ||
	    DAT_800a44fc[*(int *)((char *)p + 0x2e8)].fc == 0xb000) {
		FUN_8004b250(8, 0x2000, 0);
		FUN_8004b250(2, 0x2000, 0);
	} else {
		if (Redbook_Rnd__Fi(2))
			FUN_8004b250(9, 0x2000, 0);
		else
			FUN_8004b250(10, 0x2000, 0);
	}

	p->f6dc = 0;
}
