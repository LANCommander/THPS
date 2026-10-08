/* FUN_8005609c (0x8005609c) */
struct E {
	char pad[8];
	char *n8;
	char q[328];
};

extern struct E DAT_800a44fc[];

int DAT_800d2304[2];
int DAT_800d231c[2];
int DAT_800d230c, DAT_800d2310, DAT_800d2314;

extern int DAT_800d3758[], DAT_800d3788[];

void FUN_80059618(int);
void FUN_8006edb8(int);
void ProcessNewPSX__Fi(int);
void ClearRegion__Fiii(int, int, int);
void Spool_ClearPSX__FPc(char *);
void Spool_Sync__Fv(void);

void FUN_8005609c(void) {
	int i, v, j;

	FUN_80059618(0);

	for (i = 0; i < 2; i++) {
		if (DAT_800d231c[i]) {
			ClearRegion__Fiii(DAT_800d3758[DAT_800d2304[i]], 1, 1);
			FUN_8006edb8(DAT_800d3758[DAT_800d2304[i]]);

			DAT_800d231c[i] = 0;

			if (DAT_800d2304[0] == DAT_800d2304[1])
				DAT_800d231c[1 - i] = 0;
		}
	}

	Spool_Sync__Fv();

	v = DAT_800d230c + DAT_800d2310;

	if (v >= 11)
		v -= 11;

	j = 0;

	if (DAT_800d2314 == 0)
		DAT_800d3788[v] = 1;

	for (j = 0; j < 11; j++) {
		if (DAT_800d3788[j]) {
			ProcessNewPSX__Fi(DAT_800d3758[j]);
			Spool_ClearPSX__FPc(DAT_800a44fc[j].n8);
		}
	}

	Spool_Sync__Fv();
}
