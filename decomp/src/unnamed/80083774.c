/* FUN_80083774 (0x80083774) */
/* Clips drawing to the current zone's screen box with a DR_AREA at the last OT slot (4095). */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
typedef struct { short x1, y1, x0, y0; } SBox;
typedef struct { short pad0, y; } SDispBuf;
typedef struct { u_long OT[4096]; } SOT;
SBox *DAT_800d2178;
SOT *DAT_800d21a0;
extern SDispBuf *DAT_800d1a48;
extern u_char *DAT_800d1a54;
void FUN_80083774(void)
{
	RECT r;
	DR_AREA *p;
	r.x = DAT_800d2178->x0;
	r.y = DAT_800d2178->y0 + DAT_800d1a48->y;
	p = (DR_AREA *)DAT_800d1a54;
	r.w = DAT_800d2178->x1 - DAT_800d2178->x0;
	r.h = DAT_800d2178->y1 - DAT_800d2178->y0;
	SetDrawArea(p, &r);
	{
		u_long *ot = &DAT_800d21a0->OT[4095];
		addPrim(ot, p);
	}
	DAT_800d1a54 = (u_char *)(p + 1);
}
