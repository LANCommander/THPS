/* FUN_8004cb10 (0x8004cb10) */
typedef struct {
	int a, b;
} R;

extern R DAT_800be09c[];
extern char DAT_800a12c8[];
extern char DAT_800c0a98[];
extern int DAT_800d1b60;
extern int DAT_800d1b5c;
extern int DAT_800d1698;
extern int DAT_800d169c;
extern int DAT_800d16a0;

int DAT_800d1b10;
int DAT_800d1b14;
int DAT_800d1b18;
int DAT_800d1b1c;
int DAT_800d1b04;
int DAT_800d2260;
int DAT_800d2268;
int DAT_800d2258;
char DAT_800d225c[8];
int DAT_800d1afc;
int DAT_800d1af8;

void Mem_Copy__FPvT0i(void *a, void *b, int c);
void FUN_8008c190(char *a, int b, int c);
void GameFMV_StopFMV__Fv(void);
int FUN_800912bc(int a, char *b);
void FUN_8004cc18(void);

void FUN_8004cb10(char *p) {
	int a3, a2;

	if (DAT_800d1b10 && DAT_800d1b14) {
		Mem_Copy__FPvT0i(p, (void *)DAT_800d1b18, DAT_800d1b1c);

		DAT_800d1b04 = 0;
		return;
	}

	a3 = DAT_800be09c[0].b - DAT_800be09c[0].a - DAT_800d1b5c;
	a2 = DAT_800be09c[1].b - DAT_800be09c[1].a - DAT_800d1b60;

	if (DAT_800c0a98[0])
		FUN_8008c190(DAT_800a12c8, a3, a2);

	GameFMV_StopFMV__Fv();

	DAT_800d2260 = (int)p;
	FUN_800912bc(DAT_800d2268 / 2048 + DAT_800d2258, DAT_800d225c);

	DAT_800d1afc = 1;
	DAT_800d1698 = 0;
	DAT_800d169c = 1;
	DAT_800d16a0 = 0;
	DAT_800d1af8 = 0;
	FUN_8004cc18();
}
