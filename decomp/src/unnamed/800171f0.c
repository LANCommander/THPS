/* FUN_800171f0 (0x800171f0) */
#include "names.h"
typedef struct {
	int c[34];
} B136;

typedef struct {
	int p0, p1, p2, p3;
	char pad[0x20 - 0x10];
	int f20;
	int f24;
	char pad2[0x28 - 0x28];
} Z;

typedef struct {
	char *f00;
	char pad0[0x5c - 4];
	char *f5c;
	char *f60;
	char *f64;
	char pad1[4];
	char *f6c;
	char *f70;
	char *f74;
	char *f78;
	char *f7c;
	char *f80;
	char *f84;
	char pad2[0xc4 - 0x88];
	char *fc4;
	char *fc8;
	char pad3[0x124 - 0xcc];
	char *f124;
	char pad4[0x150 - 0x128];
	char *f150;
	char *f154;
	char *f158;
	char *f15c;
	char pad5[0x164 - 0x160];
	char *f164;
	char pad6[0x180 - 0x168];
	char pad7[4];
	char *f184;
	char *f188;
	char pad8[0x1b4 - 0x18c];
	char *f1b4;
	char *f1b8;
} S;

typedef struct {
	char pad[0xc];
	int fc;
	char pad2[0x78 - 0x10];
} T;

typedef struct {
	char pad[0x830];
	int f830;
	int f834;
} W;

extern B136 DAT_8009e31c;
extern B136 DAT_800a5c64;
extern B136 DAT_800a5bdc;
extern S DAT_800a5d5c;
extern T DAT_800a5398[];
extern W DAT_800a6844;
extern char DAT_800a5d2c[];
extern char DAT_800a5d44[];
extern int DAT_800d16a4, DAT_800d1e28;

int DAT_800d1428, DAT_800d142c, DAT_800d1430, DAT_800d1434, DAT_800d1438, DAT_800d143c,
    DAT_800d1440, DAT_800d21fc, DAT_800d2200;

void (*DAT_800d1408)(void);
void FUN_80071fa4(void);
void CMenu_AddEntry(int, char *);
void CMenu_CentreY(int);
void CMenu_EntryOff(int, char *);
int CMenu_ctor(int, int, int, int, int, int, int);
void FUN_8008b900();
int CMenu_FindEntry(int, char *);
void CMenu_SetLine(int, int);
int __nw__6CClassUi(int);

void FUN_800171f0(void) {
	int q, q2, a1, a2, a3, a4, a5, a6, a7;

	DAT_800d1408 = FUN_80071fa4;
	DAT_800a5c64 = DAT_8009e31c;
	DAT_800a5bdc = DAT_8009e31c;
	a1 = __nw__6CClassUi(384);

	if (a1)
		a1 = CMenu_ctor(a1, 256, 0, 0, 335, 256, 22);

	DAT_800d1428 = a1;
	CMenu_AddEntry(a1, DAT_800a5d5c.f1b4);
	CMenu_AddEntry(DAT_800d1428, DAT_800a5d5c.f1b8);

	a2 = __nw__6CClassUi(384);

	if (a2)
		a2 = CMenu_ctor(a2, 256, 0, 0, 335, 256, 22);

	DAT_800d142c = a2;
	CMenu_AddEntry(a2, DAT_800a5d5c.f164);
	CMenu_AddEntry(DAT_800d142c, (DAT_800a5398[DAT_800d1e28].fc && DAT_800d16a4 == 1)
	                                      ? DAT_800a5d5c.f78
										  : DAT_800a5d5c.f74);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f00);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f7c);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f80);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f84);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f70);
	CMenu_AddEntry(DAT_800d142c, DAT_800a5d5c.f188);

	if (DAT_800d16a4 != 1) {
		CMenu_EntryOff(DAT_800d142c, DAT_800a5d5c.f70);

		if (DAT_800d16a4 != 1)
			goto off0;
	}

	if (DAT_800a5398[DAT_800d1e28].fc) {
	off0:
		CMenu_EntryOff(DAT_800d142c, DAT_800a5d5c.f00);
	}

	if (DAT_800d16a4 != 3)
		CMenu_EntryOff(DAT_800d142c, DAT_800a5d5c.f164);

	if (DAT_800d16a4 == 2 || DAT_800d16a4 == 7)
		CMenu_EntryOff(DAT_800d142c, DAT_800a5d5c.f84);

	CMenu_CentreY(DAT_800d142c);
	CMenu_SetLine(
	    DAT_800d142c,
	    CMenu_FindEntry(DAT_800d142c, (DAT_800a5398[DAT_800d1e28].fc && DAT_800d16a4 == 1)
	                                           ? DAT_800a5d5c.f78
											   : DAT_800a5d5c.f74) &
	        255);

	a3 = __nw__6CClassUi(384);

	if (a3)
		a3 = CMenu_ctor(a3, 256, 0, 0, 335, 256, 22);

	DAT_800d1430 = a3;
	CMenu_AddEntry(a3, DAT_800a5d5c.f5c);
	CMenu_AddEntry(DAT_800d1430, DAT_800a5d5c.f60);
	CMenu_AddEntry(DAT_800d1430, DAT_800a5d5c.f64);
	CMenu_AddEntry(DAT_800d1430, DAT_800a5d5c.f6c);
	CMenu_CentreY(DAT_800d1430);

	a4 = __nw__6CClassUi(384);

	if (a4)
		a4 = CMenu_ctor(a4, 256, 0, 0, 335, 256, 22);

	DAT_800d1434 = a4;
	CMenu_AddEntry(a4, DAT_800a5d5c.f5c);
	CMenu_AddEntry(DAT_800d1434, DAT_800a5d5c.f60);
	CMenu_AddEntry(DAT_800d1434, DAT_800a5d5c.f6c);
	CMenu_CentreY(DAT_800d1434);

	a5 = __nw__6CClassUi(384);

	if (a5)
		a5 = CMenu_ctor(a5, 256, 0, 0, 335, 256, 22);

	DAT_800d1438 = a5;
	CMenu_AddEntry(a5, DAT_800a5d5c.f5c);
	CMenu_AddEntry(DAT_800d1438, DAT_800a5d5c.f60);
	CMenu_AddEntry(DAT_800d1438, DAT_800a5d5c.f64);
	CMenu_AddEntry(DAT_800d1438, DAT_800a5d5c.f124);
	CMenu_CentreY(DAT_800d1438);

	a6 = __nw__6CClassUi(384);

	if (a6)
		a6 = CMenu_ctor(a6, 256, 0, 0, 335, 256, 22);

	DAT_800d143c = a6;
	CMenu_AddEntry(a6, DAT_800a5d5c.fc4);
	CMenu_AddEntry(DAT_800d143c, DAT_800a5d5c.f84);
	CMenu_AddEntry(DAT_800d143c, DAT_800a5d5c.fc8);
	CMenu_AddEntry(DAT_800d143c, DAT_800a5d5c.f188);
	CMenu_CentreY(DAT_800d143c);

	a7 = __nw__6CClassUi(384);

	if (a7)
		a7 = CMenu_ctor(a7, 256, 0, 0, 335, 256, 22);

	DAT_800d1440 = a7;
	q = (DAT_800a6844.f830 + 1) * 10 / 12;
	DAT_800d21fc = q;
	FUN_8008b900(DAT_800a5d2c, DAT_800a5d5c.f150, q);
	CMenu_AddEntry(DAT_800d1440, DAT_800a5d2c);

	q2 = (DAT_800a6844.f834 + 1) * 10 / 12;
	DAT_800d2200 = q2;
	FUN_8008b900(DAT_800a5d44, DAT_800a5d5c.f154, q2);
	CMenu_AddEntry(DAT_800d1440, DAT_800a5d44);
	CMenu_AddEntry(DAT_800d1440, DAT_800a5d5c.f158);
	CMenu_AddEntry(DAT_800d1440, DAT_800a5d5c.f15c);
	CMenu_CentreY(DAT_800d1440);
}
