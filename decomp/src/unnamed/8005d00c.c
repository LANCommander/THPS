/* FUN_8005d00c (0x8005d00c) */
/* Front-end screen setup (next to FUN_8005cba0): loads the level's two pictures, builds the three
   sprites and draws the got-tape markers. buf is an unused 40-byte local kept for the frame size. */
typedef struct {
	char p[0x30];
	int f30, f34;
	char q[0x78 - 0x38];
} E;

extern E DAT_800a5398[];

typedef struct {
	char pad0[12];
	unsigned char Tapes[2];
} SC;

extern SC DAT_800a6844[];
extern char DAT_800a1b4c[], DAT_800a1b58[], DAT_800c0a48[];

int DAT_800d1cf4, DAT_800d234c;
int DAT_800d1d0c, DAT_800d1d04, DAT_800d1d00;
unsigned char DAT_800d1d18;
int DAT_800d1cec, DAT_800d1d14;

void FUN_8005c8dc(int);
void FUN_8005c97c(int);
void FUN_8005ca64(void);
int FUN_8004c8a4(int);
int FUN_8004d068(int, int, int);
void FUN_8004cb10(int);
void FUN_8004cdd0(void);
void FUN_80061a10(int);
void FUN_8005dc58(int);
int __nw__5CItemUi(int);
int FUN_80063a5c(int, int, int, int, int, int, int);
int FUN_8005ca3c(char *);
void FUN_8006b240(void);
void FUN_80061ea0(void);
void draw__6Spriteiiiiii(int, int, int, int, int, int, int);
void FUN_8006b26c(void);
void Pack_DefragmentFully__Fv(void);

void FUN_8005d00c(void) {
	char buf[40];
	int s1, o, o2, o3, i, y;

	FUN_8005c8dc(4);
	FUN_8005c97c(4);
	FUN_8005ca64();

	s1 = FUN_8004d068(FUN_8004c8a4(DAT_800a5398[DAT_800d1cf4].f30), 1, 1);
	FUN_8004cb10(s1);
	FUN_8004cdd0();
	FUN_80061a10(s1);
	FUN_8005dc58(6);

	s1 = FUN_8004d068(FUN_8004c8a4(DAT_800a5398[DAT_800d1cf4].f34), 1, 1);
	FUN_8004cb10(s1);
	FUN_8004cdd0();

	o = __nw__5CItemUi(24);

	if (o)
		o = FUN_80063a5c(o, 8, s1, 0, 458, 64, 128);

	DAT_800d1d0c = o;
	o2 = __nw__5CItemUi(24);

	if (o2)
		o2 = FUN_80063a5c(o2, 8, FUN_8005ca3c(DAT_800a1b4c), 0, 440, 64, 128);

	DAT_800d1d04 = o2;
	DAT_800d1d18 = DAT_800a6844[DAT_800d234c].Tapes[DAT_800d1cf4];
	o3 = __nw__5CItemUi(24);

	if (o3)
		o3 = FUN_80063a5c(o3, 8, FUN_8005ca3c(DAT_800a1b58), 0, 256, 64, 128);

	DAT_800d1d00 = o3;
	FUN_8006b240();
	FUN_80061ea0();

	y = 39;

	for (i = 0; i < 5; i++) {
		if ((DAT_800d1d18 >> i) & 1)
			draw__6Spriteiiiiii(DAT_800d1d00, 33, y, 0, -1, -1, -1);

		y += 26;
	}

	FUN_8006b26c();

	DAT_800c0a48[0xe1] = 0;
	DAT_800c0a48[0x24d] = 0;
	DAT_800d1cec = 0;
	DAT_800d1d14 = 0;
	Pack_DefragmentFully__Fv();
	FUN_8006b240();
	FUN_80061ea0();
}
