/* FUN_80056394 (0x80056394) */
/* Full-screen DR_AREA added at OT slot 39; FUN_8005948c is a byte-identical copy. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
extern u_long *DAT_800d1a48;
extern u_char *DAT_800d1a54;
void FUN_80056394(void)
{
	DR_AREA *p = (DR_AREA *)DAT_800d1a54;
	RECT r;
	setRECT(&r, 0, 0, 640, 480);
	SetDrawArea(p, &r);
	{
		u_long *ot = DAT_800d1a48 + 39;
		addPrim(ot, p);
	}
	DAT_800d1a54 = (u_char *)(p + 1);
}
