/* Panel_DrawFlatShadedPoly__FiiiiUcUcUci (0x8006c610) flags=-fstructure-noalias */
/* C++ (PANEL.CPP). Demo twin; locals from its MAIN.SYM. Adds a flat-shaded rectangle to the
   ordering table at the given depth; returns the primitive, or 0 if the primitive buffer is full. */
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

extern SDB *DAT_800d1a48;
extern uchar *DAT_800d1a54;
extern uchar *DAT_800d177c;

POLY_F4 *Panel_DrawFlatShadedPoly(int x, int y, int w, int h, uchar r, uchar g, uchar b, int sort) {
	POLY_F4 *apoly = (POLY_F4 *)DAT_800d1a54;
	uchar *newppoly = DAT_800d1a54 + sizeof(POLY_F4);

	if (newppoly > DAT_800d177c)
		return 0;

	DAT_800d1a54 = newppoly;
	setPolyF4(apoly);
	setRGB0(apoly, r, g, b);
	setXY4(apoly, x, y, x + w, y, x, y + h, x + w, y + h);
	addPrim(&DAT_800d1a48->OT[sort], apoly);
	return apoly;
}
