/* Graffiti_Stats__FP6CBruceiiiiiiiii (0x80017abc) */
typedef struct {
	char _0[496];
	int f496, f500;
} CBruce;

extern char DAT_800d147c[], DAT_800d1484[], DAT_800d148c[], DAT_800d1494[], DAT_800d149c[],
    DAT_800d14a4[], DAT_800d14ac[];

void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void FUN_8001d250(int);
int FUN_8001e114(int, int, char *, int, int, int, int);
int FUN_8008b900(char *, char *, int);

void Graffiti_Stats__FP6CBruceiiiiiiiii(CBruce *b, int x, int y, int r, int g, int bl, int v1,
                                        int v2, int v3, int v4) {
	char buf[16];

	Mess_SetRGB__FUcUcUci(r, g, bl, 0);
	FUN_8001d250(1);
	FUN_8001e114(x + 20, y, DAT_800d147c, 0, 0, 256, 0);
	FUN_8001e114(x + 20, y + 17, DAT_800d1484, 0, 0, 256, 0);
	FUN_8001e114(x + 20, y + 51, DAT_800d148c, 0, 0, 256, 0);
	FUN_8001e114(x + 20, y + 68, DAT_800d1494, 0, 0, 256, 0);
	FUN_8001e114(x + 20, y + 85, DAT_800d149c, 0, 0, 256, 0);
	FUN_8001e114(x + 20, y + 102, DAT_800d14a4, 0, 0, 256, 0);
	FUN_8001d250(2);
	FUN_8008b900(buf, DAT_800d14ac, b->f496);
	FUN_8001e114(x + 136, y, buf, 0, 0, 256, 0);
	FUN_8008b900(buf, DAT_800d14ac, b->f500);
	FUN_8001e114(x + 136, y + 17, buf, 0, 0, 256, 0);
	FUN_8008b900(buf, DAT_800d14ac, v4);
	FUN_8001e114(x + 136, y + 51, buf, 0, 0, 256, 0);
	FUN_8008b900(buf, DAT_800d14ac, v1);
	FUN_8001e114(x + 136, y + 68, buf, 0, 0, 256, 0);
	FUN_8008b900(buf, DAT_800d14ac, v2);
	FUN_8001e114(x + 136, y + 85, buf, 0, 0, 256, 0);
	FUN_8008b900(buf, DAT_800d14ac, v3);
	FUN_8001e114(x + 136, y + 102, buf, 0, 0, 256, 0);
}
