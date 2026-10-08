/* FUN_800494dc (0x800494dc) */
typedef struct {
	short x, y, w, h;
} R;

extern int pBMR;

char *pDoubleBuffer;
int DAT_800d1a38;

void FUN_8008c1a0(int a);
void FUN_8008c94c(char *a);
int FUN_8008ca0c(char *a);
void FUN_8008c714(R *r, int a);
void FUN_8008c468(int a);
int FUN_80048c74(void);
int FUN_80089ddc(char *a, int b);
void FUN_8008c8dc(char *a);

void FUN_800494dc(void) {
	R r;

	FUN_8008c1a0(1);
	FUN_8008c94c(pDoubleBuffer);
	FUN_8008ca0c(pDoubleBuffer + 92);

	if (DAT_800d1a38 && pBMR) {
		r.x = 0;
		r.y = *(unsigned short *)(pDoubleBuffer + 32768 + 144);
		r.w = 512;
		r.h = 240;
		FUN_8008c714(&r, pBMR);
		FUN_8008c468(0);
	} else {
		DAT_800d1a38 = 0;
	}

	FUN_80089ddc(pDoubleBuffer + 132, FUN_80048c74());

	if (DAT_800d1a38)
		FUN_8008c468(0);

	FUN_8008c8dc((char *)(FUN_80048c74() * 4) + (int)pDoubleBuffer + 128);
}
