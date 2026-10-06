/* SetClippingBox__Fiiii (0x80061e00) flags=-fstructure-noalias */
/* SHELLUTILS.CPP, as C (demo twin; locals from its MAIN.SYM). Adds a DR_AREA for the rectangle to the
   current frame's per-call layer OT (which counts down), so later 2D prims are clipped to it. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
typedef struct {
	char pad0[140];
	u_long Layer[1];            /* 140 */
} SOTBuffer;
extern SOTBuffer *DAT_800d1a48;
extern u_char *DAT_800d1a54;
int DAT_800d1d94;

void SetClippingBox__Fiiii(int x, int y, int w, int h)
{
	RECT r;
	DR_AREA *pClip = (DR_AREA *)DAT_800d1a54;
	setRECT(&r, x, y, w, h);
	SetDrawArea(pClip, &r);
	DAT_800d1a54 = (u_char *)(pClip + 1);
	addPrim(&DAT_800d1a48->Layer[DAT_800d1d94], pClip);
	DAT_800d1d94--;
}
