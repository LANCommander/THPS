/* FUN_8005dcc4 (0x8005dcc4) */
/* Draws the countdown bar started by FUN_8005dc58: elapsed vblanks since the start, capped at the
   total, as a 400x8 bar (dark red, filling) at one of three screen positions; a full blue bar once
   time is up or when no total is set. FUN_8008c5ec is ClearImage (it returns a value). */
typedef struct {
	short x, y, w, h;
} R;

extern unsigned short DAT_800bf0f0[];
extern unsigned short DAT_800bf0fc[];
extern unsigned short DAT_800bf0ec[];
extern unsigned short DAT_800bf0f8[];
extern unsigned short DAT_800bf0f4[];
extern unsigned short DAT_800bf100[];

int DAT_800d1cf0;
int DAT_800d1ce4;
int DAT_800d1cd8;
unsigned DAT_800d1ce0;
unsigned DAT_800d1cdc;
int DAT_800d1cf8;

extern unsigned DAT_800d1a20;

int FUN_8008c5ec(R *r, int red, int green, int blue);

void FUN_8005dcc4(void) {
	R r;

	if (DAT_800d1cf0)
		return;

	if (!DAT_800d1ce4)
		return;

	DAT_800d1cdc = DAT_800d1a20 - DAT_800d1cd8;

	if (DAT_800d1ce0 < DAT_800d1cdc)
		DAT_800d1cdc = DAT_800d1ce0;

	if (DAT_800d1cf8 == 4) {
		r.x = DAT_800bf0f0[0];
		r.y = DAT_800bf0fc[0];
	} else if (DAT_800d1cf8 == 0) {
		r.x = DAT_800bf0ec[0];
		r.y = DAT_800bf0f8[0];
	} else {
		r.x = DAT_800bf0f4[0];
		r.y = DAT_800bf100[0];
	}

	r.w = 0;
	r.h = 8;

	if (DAT_800d1ce0 == 0 || DAT_800d1ce0 < DAT_800d1cdc) {
		r.w = 400;
		FUN_8008c5ec(&r, 0, 0, 255);
	} else {
		r.w = (DAT_800d1cdc * 400) / DAT_800d1ce0;
		FUN_8008c5ec(&r, 150, 0, 0);
	}
}
