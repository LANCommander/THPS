/* Front_ClearScreen__Fv (0x80017148) */
typedef struct {
	short x, y, w, h;
} RECT;

extern int DAT_800d1a1c;
extern RECT DAT_800d1444[];

int FUN_8008c5ec(RECT *, int, int, int);
int FUN_8008c468(int);

void Front_ClearScreen(void) {
	RECT r;

	DAT_800d1a1c = 0;
	r = DAT_800d1444[0];
	FUN_8008c5ec(&r, 0, 0, 0);
	FUN_8008c468(0);

	r.y = 511;
	r.h = 1;
	FUN_8008c5ec(&r, 0, 0, 0);
	FUN_8008c468(0);
}
