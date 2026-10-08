/* SetClippingBox__Fiiii (0x80061e00) flags=-fstructure-noalias */
#include "names.h"
/* SHELLUTILS.CPP, as C (demo twin; locals from its MAIN.SYM). Adds a DR_AREA for the rectangle to the
   current frame's per-call layer OT (which counts down), so later 2D prims are clipped to it. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct {
	char pad0[140];
	u_long Layer[1]; /* 140 */
} SOTBuffer;

extern SOTBuffer *pDoubleBuffer;
extern u_char *pPoly;

int OT_entry;

void SetClippingBox(int x, int y, int w, int h) {
	RECT r;
	DR_AREA *pClip = (DR_AREA *)pPoly;

	setRECT(&r, x, y, w, h);
	SetDrawArea(pClip, &r);

	pPoly = (u_char *)(pClip + 1);
	addPrim(&pDoubleBuffer->Layer[OT_entry], pClip);

	OT_entry--;
}
