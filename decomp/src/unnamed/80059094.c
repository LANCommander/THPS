/* FUN_80059094 (0x80059094) */
struct E {
	char pad[8];
	char *n8;
	char pad2[328];
};

extern struct E DAT_800a44fc[];
extern int DAT_800d37e4[];
extern int DAT_800d37b4[];

int DAT_800d2338;
int DAT_800d2324;
int DAT_800d233c;
int DAT_800d2340;

void FileIO_Continue__Fv(void);
void Spool_Continue__Fv(void);
int FUN_80070830(void);
void Spool_Sync__Fv(void);
int Spool_PSX__FPciii(char *a, int b, int c);

void FUN_80059094(void) {
	int a;
	int n;

	FileIO_Continue__Fv();
	Spool_Continue__Fv();

	if (FUN_80070830())
		return;

	Spool_Sync__Fv();

	a = DAT_800d2338;

	if (a >= 0)
		DAT_800d37e4[DAT_800d2324] = 1;

	if (a == -1) {
		DAT_800d2338 = 0;
	} else {
		if (a < 5)
			n = 10;
		else if (a < 6) {
			DAT_800d2340 = 1;
			return;
		} else
			n = 11;

		DAT_800d2338 = n - a;
	}

	DAT_800d2324 = DAT_800d2338 + DAT_800d233c;

	if (!(DAT_800d2324 < 11))
		DAT_800d2324 = DAT_800d2324 - 11;

	if (*DAT_800a44fc[DAT_800d2324].n8)
		DAT_800d37b4[DAT_800d2324] = Spool_PSX__FPciii(DAT_800a44fc[DAT_800d2324].n8, 2, 1);
}
