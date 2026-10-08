/* FUN_8006af64 (0x8006af64) */
/* Blanks the display: clears the screen rectangle and the bottom VRAM line, then re-puts the
   draw environment with dithering-on-display and background clear turned off. */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern RECT DAT_800d1e20[];
extern DRAWENV DAT_800a891c;

void FUN_8006af64(void) {
	RECT r;

	SetDispMask(0);

	r = DAT_800d1e20[0];
	ClearImage(&r, 0, 0, 0);
	DrawSync(0);

	r.y = 511;
	r.h = 1;
	ClearImage(&r, 0, 0, 0);
	DrawSync(0);

	DAT_800a891c.dfe = 0;
	DAT_800a891c.isbg = 0;
	PutDrawEnv(&DAT_800a891c);
	SetDispMask(1);
}
