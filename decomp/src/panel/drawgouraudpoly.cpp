/* DrawGouraudPoly__FiiiiUcUcUcUcUcUci (0x8006c6e4) flags=-fstructure-noalias */
/* C++ (PANEL.CPP). Demo twin; locals from its MAIN.SYM. Adds a Gouraud-shaded rectangle (left
   edge in the bottom colour, right edge in the top colour) to the ordering table at the given
   depth; returns the primitive, or 0 if the primitive buffer is full. */
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

POLY_G4 *DrawGouraudPoly(int x, int y, int w, int h, uchar rtop, uchar gtop, uchar btop, uchar rbottom, uchar gbottom,
	uchar bbottom, int sort)
{
	POLY_G4 *apoly = (POLY_G4 *)DAT_800d1a54;
	uchar *newppoly = DAT_800d1a54 + sizeof(POLY_G4);
	if (newppoly > DAT_800d177c)
		return 0;
	DAT_800d1a54 = newppoly;
	setPolyG4(apoly);
	apoly->r0 = rbottom; apoly->r1 = rtop;
	apoly->g0 = gbottom; apoly->g1 = gtop;
	apoly->b0 = bbottom; apoly->b1 = btop;
	apoly->r2 = rbottom; apoly->r3 = rtop;
	apoly->g2 = gbottom; apoly->g3 = gtop;
	apoly->b2 = bbottom; apoly->b3 = btop;
	apoly->x0 = x; apoly->x1 = x + w;
	apoly->y0 = y; apoly->y1 = y;
	apoly->x2 = x; apoly->x3 = x + w;
	apoly->y2 = y + h; apoly->y3 = y + h;
	addPrim(&DAT_800d1a48->OT[sort], apoly);
	return apoly;
}
