/* FUN_800591c0 (0x800591c0) */
struct E {
	char pad[8];
	char *n8;
	char q[328];
};

extern struct E DAT_800a44fc[];

int DAT_800d2344, DAT_800d1c40, DAT_800d2338, DAT_800d233c, DAT_800d2340;

extern int DAT_800d37b4[], DAT_800d37e4[];

void FUN_800596a0(void);
void FUN_8006edb8(int);
void ProcessNewPSX__Fi(int);
void ClearRegion__Fiii(int, int, int);
void Spool_ClearPSX__FPc(char *);
void Spool_Sync__Fv(void);

void FUN_800591c0(void) {
	int i, v;

	if (DAT_800d2344 && *DAT_800a44fc[DAT_800d1c40].n8) {
		ClearRegion__Fiii(DAT_800d37b4[DAT_800d1c40], 1, 1);
		FUN_8006edb8(DAT_800d37b4[DAT_800d1c40]);
	}

	Spool_Sync__Fv();

	v = DAT_800d2338 + DAT_800d233c;

	if (v >= 11)
		v -= 11;

	i = 0;

	if (DAT_800d2340 == 0)
		DAT_800d37e4[v] = 1;

	for (i = 0; i < 11; i++) {
		if (*DAT_800a44fc[i].n8 && DAT_800d37e4[i]) {
			FUN_800596a0();
			ProcessNewPSX__Fi(DAT_800d37b4[i]);
			Spool_ClearPSX__FPc(DAT_800a44fc[i].n8);
		}
	}

	Spool_Sync__Fv();
}
