/* Front_MemCardDisplay__Fv (0x80011820) */
/* Memory-card front-end screen (RFRONT.CPP), as C. The save-slot list loop follows the demo twin:
   x is XMid - 150 + i * 30 (no separate column variable), and the slot letter goes into a copy of a
   3-byte template in buf. */
typedef struct {
	char pad0[0xc];
	char *f0c;
	char *f10;
	char pad1[0x18 - 0x14];
	char *f18;
	char *f1c;
	char pad2[0xd0 - 0x20];
	char *fd0;
	char pad3[4];
	char *fd8;
	char pad4[0x180 - 0xdc];
	char *f180;
	char pad5[0x1c8 - 0x184];
	char *f1c8;
	char *f1cc;
	char *f1d0;
	char *f1d4;
	char *f1d8;
	char *f1dc;
	char *f1e0;
	char *f1e4;
	char pad6[0x1f8 - 0x1e8];
	char *f1f8;
	char *f1fc;
	char *f200;
	char pad7[4];
	char *f208;
	char *f20c;
	char *f210;
	char *f214;
	char *f218;
	char *f21c;
	char pad8[0x228 - 0x220];
	char *f228;
	char pad9[0x234 - 0x22c];
	char *f234;
	char pad10[0x244 - 0x238];
	char *f244;
} S;

typedef struct {
	char pad[0x10];
	int f10;
} O;

extern S DAT_800a5d5c;
extern char *DAT_800a5d90[];
extern char *DAT_800a5f50[];
extern char *DAT_800a5f98[];
extern char *DAT_800a5f9c[];
extern char DAT_8009d0f0[];
extern char DAT_8009d11c[];
extern char DAT_800a42d0[];
extern char DAT_800d112c[];
extern char DAT_800d1130[];
extern char DAT_800d1134[];

typedef struct {
	char a, b, c;
} T3;

extern char DAT_800d1138[];
extern O *DAT_800d1428;
extern int DAT_800d16e4;

unsigned DAT_800d111c;
int DAT_800d1128;
int DAT_800d10fc, DAT_800d1100, DAT_800d1144, DAT_800d21d8, DAT_800d21dc;

void FUN_80011214(void);
void FUN_8001696c(O *);
void FUN_8001d250(int);
int FUN_8001e114(int, int, char *, int, int, int, int);
void FUN_8008b900(char *, char *, int, char *);
void Front_PrintCentredPrompt__FPCc(char *);
void Front_PrintGoBackSelect__Fv(void);
void Mess_SetRGB__FUcUcUci(int, int, int, int);
void Mess_SetScale__Fi(int);
void RGBRed__Fv(void);

void FUN_80011820(void) {
	int s2, s0, s1, t;
	char buf[24];
	unsigned char c;
	O *o;
	char *a;

	s2 = DAT_800d1128 >> 1;
	Mess_SetScale__Fi(256);
	FUN_8001d250(0);

	switch (DAT_800d111c) {
		case 0:
		case 1:
		case 15:
		case 16:
			FUN_80011214();
			FUN_8001e114(s2, 90, DAT_800a5d5c.f200, 0, 0, 256, 0);
			RGBRed__Fv();
			FUN_8001e114(s2, 140, DAT_800a5d5c.f1f8, 0, 0, 256, 0);
			FUN_8001e114(s2, 166, DAT_800a5d5c.f1fc, 0, 0, 256, 0);
			break;
		case 9:
		case 17:
			RGBRed__Fv();
			FUN_8001e114(s2, 90, DAT_800a5d5c.f1c8, 0, 0, 256, 0);
			FUN_8001e114(s2, 116, DAT_800a5d5c.f1cc, 0, 0, 256, 0);
			FUN_8001e114(s2, 142, DAT_800a5d5c.f1d0, 0, 0, 256, 0);
			FUN_8001e114(s2, 168, DAT_800a5d5c.f1d4, 0, 0, 256, 0);
			break;
		case 10:
			Front_PrintGoBackSelect__Fv();
			RGBRed__Fv();
			FUN_8001e114(s2, 35, DAT_800a5d5c.f1d8, 0, 0, 256, 0);
			FUN_8001e114(s2, 61, DAT_800a5d5c.f1dc, 0, 0, 256, 0);
			FUN_8001e114(s2, 87, DAT_800a5d5c.f1e0, 0, 0, 256, 0);
			FUN_8001e114(s2, 113, DAT_800a5d5c.f1e4, 0, 0, 256, 0);

			o = DAT_800d1428;
			o->f10 = 148;
			FUN_8001696c(o);
			break;
		case 11:
			FUN_80011214();

			if ((DAT_800d16e4 / 10) & 1)
				FUN_8001e114(s2, 110, DAT_800a5f50[0], 0, 0, 256, 0);

			RGBRed__Fv();
			FUN_8001e114(s2, 140, DAT_800a5d5c.f1f8, 0, 0, 256, 0);
			FUN_8001e114(s2, 166, DAT_800a5d5c.f1fc, 0, 0, 256, 0);
			break;
		case 13:
			FUN_80011214();
			FUN_8001e114(s2, 110, DAT_800a5f9c[0], 0, 0, 256, 0);
			break;
		case 12:
			RGBRed__Fv();
			FUN_8001e114(s2, 110, DAT_800a5f98[0], 0, 0, 256, 0);
			break;
		case 8:
			RGBRed__Fv();
			Mess_SetScale__Fi(192);
			FUN_8001e114(s2, 67, DAT_800a5d5c.f208, 0, 0, 256, 0);
			FUN_8001e114(s2, 85, DAT_800a5d5c.f20c, 0, 0, 256, 0);
			FUN_8001e114(s2, 103, DAT_800a5d5c.f210, 0, 0, 256, 0);
			FUN_8008b900(buf, DAT_800a5d5c.f214, DAT_800d21d8,
			             DAT_800d21d8 == 1 ? DAT_800d112c : DAT_800d1130);
			FUN_8001e114(s2, 121, buf, 0, 0, 256, 0);
			FUN_8008b900(buf, DAT_800a5d5c.f218, DAT_800d21d8 - DAT_800d21dc,
			             DAT_800d21d8 - DAT_800d21dc == 1 ? DAT_800d112c : DAT_800d1130);
			FUN_8001e114(s2, 139, buf, 0, 0, 256, 0);
			FUN_8001e114(s2, 157, DAT_800a5d5c.f21c, 0, 0, 256, 0);
			Front_PrintCentredPrompt__FPCc(DAT_800a5d5c.f180);
			break;
		case 3:
			FUN_80011214();
			FUN_8001e114(s2, 50, DAT_800a5d5c.f18, 0, 0, 256, 0);
			FUN_8001e114(s2, 76, DAT_800a5d5c.f1c, 0, 0, 256, 0);
			FUN_8001e114(s2, 102, DAT_800a5d5c.f228, 0, 0, 256, 0);
			Front_PrintGoBackSelect__Fv();

			o = DAT_800d1428;
			o->f10 = 145;
			FUN_8001696c(o);
			break;
		case 4:
			FUN_80011214();
			FUN_8001e114(s2, 110, DAT_800a5d5c.f234, 0, 0, 256, 0);
			RGBRed__Fv();
			FUN_8001e114(s2, 140, DAT_800a5d5c.f1f8, 0, 0, 256, 0);
			FUN_8001e114(s2, 166, DAT_800a5d5c.f1fc, 0, 0, 256, 0);
			break;
		case 7:
			FUN_80011214();
			FUN_8001e114(s2, 110, DAT_800a5d5c.fd0, 0, 0, 256, 0);
			Front_PrintCentredPrompt__FPCc(DAT_800a5d5c.f180);
			break;
		case 6:
			RGBRed__Fv();
			FUN_8001e114(s2, 110, DAT_800a5d5c.fd8, 0, 0, 256, 0);
			Front_PrintCentredPrompt__FPCc(DAT_800a5d5c.f180);
			break;
		case 2:
			s0 = 0;
			RGBRed__Fv();
			FUN_8001d250(0);
			Mess_SetScale__Fi(256);
			FUN_8001e114(s2, 40, DAT_800a5d90[0], 0, 0, 256, 0);

			do {
				if (DAT_800d1100 > 0)
					DAT_800d1100--;

				Mess_SetScale__Fi(256);

				if (s0 == DAT_800d10fc)
					Mess_SetRGB__FUcUcUci(182, 132, 36, 0);
				else
					Mess_SetRGB__FUcUcUci(122, 122, 122, 0);

				FUN_8001e114(s2 - 150 + s0 * 30, 100, DAT_800d1134, 0, 0, 256, 0);

				if (s0 == DAT_800d10fc)
					Mess_SetScale__Fi(DAT_800d1100 * 6 + 256);

				if (DAT_800a42d0[s0]) {
					*(T3 *)buf = *(T3 *)DAT_800d1138;
					buf[0] = DAT_800a42d0[s0];
					FUN_8001e114(s2 - 150 + s0 * 30, 92, buf, 0, 0, 256, 0);
				}

				s0++;
			} while (s0 < 10);

			Front_PrintGoBackSelect__Fv();
			break;
		case 14:
			FUN_8001e114(s2, 100, DAT_8009d0f0, 0, 0, 256, 0);
			break;
		case 19:
			RGBRed__Fv();

			if (DAT_800d1144 == 2)
				FUN_8001e114(s2, 110, DAT_800a5d5c.f10, 0, 0, 256, 0);
			else
				FUN_8001e114(s2, 110, DAT_800a5d5c.f0c, 0, 0, 256, 0);

			if (DAT_800d1128 == 512)
				Front_PrintCentredPrompt__FPCc(DAT_800a5d5c.f180);

			break;
		case 20:
			if (DAT_800d1128 == 512)
				Front_PrintGoBackSelect__Fv();

			break;
		case 21:
			FUN_80011214();
			FUN_8001e114(s2, 110, DAT_8009d11c, 0, 0, 256, 0);
			RGBRed__Fv();
			FUN_8001e114(s2, 140, DAT_800a5d5c.f1f8, 0, 0, 256, 0);
			FUN_8001e114(s2, 166, DAT_800a5d5c.f1fc, 0, 0, 256, 0);
			break;
		case 22:
			RGBRed__Fv();
			FUN_8001e114(s2, 110, DAT_800a5d5c.f244, 0, 0, 256, 0);

			if (DAT_800d1128 == 512)
				Front_PrintCentredPrompt__FPCc(DAT_800a5d5c.f180);

			break;
		case 23:
			break;
	}
}
