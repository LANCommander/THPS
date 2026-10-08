/* FUN_80055f80 (0x80055f80) */
struct E {
	char pad[8];
	char *n8;
	char pad2[328];
};

extern struct E DAT_800a44fc[];
extern int DAT_800d3788[];
extern int DAT_800d3758[];

int DAT_800d230c;
int DAT_800d22f4;
int DAT_800d2310;
int DAT_800d2314;

void FUN_8004cc18(void);
void FUN_8007046c(void);
int FUN_80070830(void);
void Spool_Sync__Fv(void);
int FUN_800701b0(char *a, int b, int c);

void FUN_80055f80(void) {
	int a;
	int n;

	FUN_8004cc18();
	FUN_8007046c();

	if (FUN_80070830())
		return;

	Spool_Sync__Fv();

	a = DAT_800d230c;

	if (a >= 0)
		DAT_800d3788[DAT_800d22f4] = 1;

	if (a == -1) {
		DAT_800d230c = 0;
	} else {
		if (a < 5)
			n = 10;
		else if (a < 6) {
			DAT_800d2314 = 1;
			return;
		} else
			n = 11;

		DAT_800d230c = n - a;
	}

	DAT_800d22f4 = DAT_800d230c + DAT_800d2310;

	if (!(DAT_800d22f4 < 11))
		DAT_800d22f4 = DAT_800d22f4 - 11;

	DAT_800d3758[DAT_800d22f4] = FUN_800701b0(DAT_800a44fc[DAT_800d22f4].n8, 2, 1);
}
