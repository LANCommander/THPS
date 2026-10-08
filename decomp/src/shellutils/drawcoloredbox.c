/* DrawColoredBox__FiiiiUcUcUc (0x80061d44) flags=-fstructure-noalias */
#include "names.h"
/* SHELLUTILS.CPP, as C (demo twin; locals from its MAIN.SYM). A flat-shaded rectangle added to the
   current frame's per-call layer OT (which counts down), like SetClippingBox. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct {
	char pad0[140];
	u_long Layer[1]; /* 140 */
} SOTBuffer;

extern SOTBuffer *DAT_800d1a48;
extern u_char *DAT_800d1a54;

int DAT_800d1d94;

void DrawColoredBox(int x, int y, int w, int h, u_char r, u_char g, u_char b) {
	POLY_F4 *Poly = (POLY_F4 *)DAT_800d1a54;

	DAT_800d1a54 = (u_char *)(Poly + 1);
	setPolyF4(Poly);
	setRGB0(Poly, r, g, b);
	setXY4(Poly, x, y, x + w, y, x, y + h, x + w, y + h);
	addPrim(&DAT_800d1a48->Layer[DAT_800d1d94], Poly);

	DAT_800d1d94--;
}
