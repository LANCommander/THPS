/* FUN_8005948c (0x8005948c) */
/* Byte-identical copy of FUN_80056394. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern u_long *pDoubleBuffer;
extern u_char *pPoly;

void FUN_8005948c(void) {
	DR_AREA *p = (DR_AREA *)pPoly;
	RECT r;

	setRECT(&r, 0, 0, 640, 480);
	SetDrawArea(p, &r);

	{
		u_long *ot = pDoubleBuffer + 39;

		addPrim(ot, p);
	}

	pPoly = (u_char *)(p + 1);
}
