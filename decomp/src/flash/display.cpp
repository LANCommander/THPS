/* Flash_Display__Fv (0x8001f4c4) flags=-fstructure-noalias */
/* C++ (FLASH.CPP). Demo twin; locals from its MAIN.SYM. While a screen flash is active, adds a
   full-screen semi-transparent flat quad in the flash colour (additive, or subtractive for the
   second mode) to the current ordering table. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <libgpu.h>
}

typedef unsigned char uchar;

struct SDB {
	char pad0[0x84];
	u_long OT[1];
};

int DAT_800d160c;

extern const int DAT_800d1610;

int DAT_800d1608;

extern SDB *DAT_800d1a48;
extern uchar *DAT_800d1a54;
extern uchar *DAT_800d177c;

volatile ushort DAT_800d220a;
volatile ushort DAT_800d220e;
volatile ushort DAT_800d2212;

void Flash_Display() {
	if (DAT_800d160c || DAT_800d1610) {
		u_long *OTPos = &DAT_800d1a48->OT[DAT_800d1608];
		POLY_F4 *aPoly = (POLY_F4 *)DAT_800d1a54;
		uchar *newppoly = DAT_800d1a54 + sizeof(POLY_F4) + sizeof(DR_TPAGE);
		DR_TPAGE *ptpage = (DR_TPAGE *)(aPoly + 1);

		if (newppoly <= DAT_800d177c) {
			DAT_800d1a54 = newppoly;
			setPolyF4(aPoly);
			setSemiTrans(aPoly, 1);
			setRGB0(aPoly, DAT_800d220a, DAT_800d220e, DAT_800d2212);

			aPoly->x0 = 0;
			aPoly->x1 = 512;
			aPoly->y0 = 0;
			aPoly->y1 = 0;
			aPoly->x2 = 0;
			aPoly->x3 = 512;
			aPoly->y2 = 240;
			aPoly->y3 = 240;
			addPrim(OTPos, aPoly);

			((u_long *)ptpage)[0] = 0x01000000;

			if (DAT_800d1610)
				((u_long *)ptpage)[1] = 0xe1000640;
			else
				((u_long *)ptpage)[1] = 0xe1000620;

			addPrim(OTPos, ptpage);
		}
	}
}

extern const int DAT_800d1610 = 0;
