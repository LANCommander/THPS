/* FUN_8006582c (0x8006582c) */
typedef struct E {
	int p;
	char s[16];
	int i14, i18, i1c;
	int used;
} E;

typedef struct C {
	int f0, f4, f8, cur;
	E e[8];
} C;

extern char DAT_800d1da4[], DAT_800d1da8[], DAT_800d1dac[], DAT_800d1db0[], DAT_800d1db4[],
    DAT_800d1db8[], DAT_800a208c[], DAT_800a20a0[];
extern int DAT_800d1b10;

int FileIO_Open__FPCc(char *);
void FUN_8004cb10(int);
void FUN_8004cdd0(void);
int Mem_NewX__FUiii(int, int, int);
void spoolPRE__10PREManagerPc(int, char *);
int Spool_PSX__FPciii(char *, int, int);
void FUN_8008c190(char *, char *);
int FUN_8008f6fc(char *, char *);
void Spool_Sync__Fv(void);

void FUN_8006582c(C *a) {
	char *s;
	int ok, n, t;
	char buf[16];

	if (a->f4 == 1)
		Spool_Sync__Fv();
	else
		FUN_8004cdd0();

	while (a->e[a->cur].used)
		a->cur++;

	a->f4 = 0;
	s = a->e[a->cur].s;

	while (*s != 95 && *s)
		s++;

	if (*s == 95) {
		s++;
		ok = 0;

		if (!FUN_8008f6fc(s, DAT_800d1da4) || !FUN_8008f6fc(s, DAT_800d1da8) ||
		    !FUN_8008f6fc(s, DAT_800d1dac) || !FUN_8008f6fc(s, DAT_800d1db0))
			ok = 1;

		if (ok)
			a->f4 = 1;
	}

	s = a->e[a->cur].s;

	while (*s != 46 && *s)
		s++;

	if (*s == 46) {
		s++;
		ok = 0;

		if (!FUN_8008f6fc(s, DAT_800d1db4) || !FUN_8008f6fc(s, DAT_800d1db8))
			ok = 1;

		if (ok)
			a->f4 = 2;
	}

	t = a->f4;

	switch (t) {
		case 1:
			a->e[a->cur].p = 0;
			a->e[a->cur].i14 = Spool_PSX__FPciii(a->e[a->cur].s, 2, 1);
			a->e[a->cur].i1c = 0;
			a->e[a->cur].i18 = t;
			break;
		case 2:
			spoolPRE__10PREManagerPc(DAT_800d1b10, a->e[a->cur].s);

			a->e[a->cur].p = 0;
			a->e[a->cur].i14 = -1;
			a->e[a->cur].i1c = 0;
			a->e[a->cur].i18 = t;
			break;
		default:
			n = FileIO_Open__FPCc(a->e[a->cur].s);

			if (n <= 0) {
				FUN_8008c190(DAT_800a208c, a->e[a->cur].s);
				return;
			}

			a->e[a->cur].p = Mem_NewX__FUiii(n, 1, 1);

			if (a->e[a->cur].p == 0) {
				FUN_8008c190(DAT_800a20a0, a->e[a->cur].s);
				return;
			}

			FUN_8004cb10(a->e[a->cur].p);

			a->e[a->cur].i14 = -1;
			a->e[a->cur].i1c = n;
			a->e[a->cur].i18 = 0;
			break;
	}

	a->e[a->cur].used = 1;
	a->cur = a->cur + 1;
}
