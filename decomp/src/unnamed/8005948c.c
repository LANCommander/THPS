/* FUN_8005948c (0x8005948c) */
/* Byte-identical copy of FUN_80056394. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
extern u_long *DAT_800d1a48;
extern u_char *DAT_800d1a54;
void FUN_8005948c(void)
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
