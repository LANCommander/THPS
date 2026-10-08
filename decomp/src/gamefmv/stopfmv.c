/* GameFMV_StopFMV__Fv (0x800233d0) */
typedef struct {
	unsigned short x, y, w, h;
} RECT;

extern int DAT_800a6748[];

int DAT_800d1634, DAT_800d1638, DAT_800d1678, DAT_800d165c, DAT_800d222c;
int DAT_800d168c[2];
unsigned char DAT_800d166c;
short DAT_800d1658;
unsigned short DAT_800d166e, DAT_800d1672, DAT_800d1674;

void FUN_8008f620(unsigned char *);
void FUN_8009035c(int);
void FUN_8009074c(void);
void FUN_800912bc(int, unsigned char *);
void FUN_8008f264(int, unsigned char *, int);
void Mem_Delete__FPv(int);
void FUN_8008c5ec(RECT *, int, int, int);

void GameFMV_StopFMV__Fv(void) {
	unsigned char p[4];
	unsigned char loc[4];
	RECT r;
	int i;

	DAT_800d1678 = 0;
	DAT_800d1638 = 0;

	if (DAT_800d1634) {
		p[0] = 0;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0;
		FUN_8008f620(p);

		DAT_800d1634 = 0;
		FUN_8009035c(0);
		FUN_8009074c();
		FUN_800912bc(DAT_800d165c, loc);
		FUN_8008f264(22, loc, 0);

		if (DAT_800d222c) {
			Mem_Delete__FPv(DAT_800d222c);

			DAT_800d222c = 0;
		}

		for (i = 0; i < DAT_800d166c; i++) {
			if (DAT_800a6748[i]) {
				Mem_Delete__FPv(DAT_800a6748[i]);

				DAT_800a6748[i] = 0;
			}
		}

		for (i = 0; i < 2; i++) {
			if (DAT_800d168c[i]) {
				Mem_Delete__FPv(DAT_800d168c[i]);

				DAT_800d168c[i] = 0;
			}
		}

		if (DAT_800d1658 != -1) {
			r.x = DAT_800d1658;
			r.y = DAT_800d166e;
			r.w = DAT_800d1672;
			r.h = DAT_800d1674;
			FUN_8008c5ec(&r, 1, 1, 1);
		}
	}
}
