/* Panel_DrawTexturedPoly__FP10SAnimFrame (0x8006c4f0) */
#include "names.h"
/* Allocates a grey-modulated POLY_FT4, copies its UVs/CLUT/TPAGE from the texture record and
   adds it at OT slot 33 (coordinates are left to the caller). Returns 0 when the primitive buffer
   is full. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct {
	u_long uv0clut, uv1tpage;
	u_short uv2, uv3;
} STexUV;

typedef struct {
	int pad;
	STexUV *pUV;
} STexture;

extern u_long *DAT_800d1a48;
extern u_char *DAT_800d1a54;
extern u_char *DAT_800d177c;

POLY_FT4 *Panel_DrawTexturedPoly(STexture *t) {
	POLY_FT4 *p = (POLY_FT4 *)DAT_800d1a54;
	u_char *next = (u_char *)(p + 1);
	STexUV *uv;

	if (next > DAT_800d177c)
		return 0;

	DAT_800d1a54 = next;
	*(u_long *)&p->tag = 0x09000000;
	*(u_long *)&p->r0 = 0x2c808080;
	uv = t->pUV;

	{
		u_long a = uv->uv0clut;
		u_long b = uv->uv1tpage;
		u_long c = *(u_long *)&uv->uv2;
		u_short d = uv->uv3;

		*(u_long *)&p->u0 = a;
		*(u_long *)&p->u1 = b;
		*(u_long *)&p->u2 = c;
		*(u_short *)&p->u3 = d;
	}

	{
		u_long *ot = DAT_800d1a48 + 33;

		addPrim(ot, p);
	}

	return p;
}
