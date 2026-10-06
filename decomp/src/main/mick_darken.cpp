/* Mick_Darken__Fv (0x80024454) */
/* C++ (MAIN.CPP). Fuzzy demo twin; locals from its MAIN.SYM. Fades a full-screen semi-transparent
   black-ish quad in (brightness climbs by 4 a frame up to 40). The corners are set in the demo's
   source-line grouping (x0/x1, y0/y1, x2/x3, y2/y3); setXY4's order schedules differently. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;

struct SOTBuffer { char pad[0x88]; u_long OT; };
extern SOTBuffer *DAT_800d1a48;
extern uchar *DAT_800d1a54;
uchar *DAT_800d177c;
int DAT_800d1738;

void Mick_Darken()
{
	POLY_F4 *aPoly;
	DR_TPAGE *ptpage;
	uchar *newppoly;
	u_long *ot = &DAT_800d1a48->OT;

	if (DAT_800d1738 < 40)
		DAT_800d1738 += 4;
	aPoly = (POLY_F4 *)DAT_800d1a54;
	newppoly = (uchar *)aPoly + sizeof(POLY_F4) + sizeof(DR_TPAGE);
	ptpage = (DR_TPAGE *)(aPoly + 1);
	if (newppoly > DAT_800d177c)
		return;
	DAT_800d1a54 = newppoly;
	setPolyF4(aPoly);
	setSemiTrans(aPoly, 1);
	setRGB0(aPoly, DAT_800d1738, DAT_800d1738, DAT_800d1738);
	aPoly->x0 = 0; aPoly->x1 = 512;
	aPoly->y0 = 0; aPoly->y1 = 0;
	aPoly->x2 = 0; aPoly->x3 = 512;
	aPoly->y2 = 240; aPoly->y3 = 240;
	addPrim(ot, aPoly);
	ptpage->tag = 0x01000000;
	ptpage->code[0] = _get_mode(1, 1, 0x40);
	addPrim(ot, ptpage);
}
