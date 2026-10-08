/* FUN_8006eb18 (0x8006eb18) */
#include "names.h"
extern int DAT_800d173c;
extern int *DAT_800d17c8;
extern char *DAT_800a5e94[];
extern char *DAT_800a5e98[];
extern char DAT_800a6070[];

void Panel_GetViewportMessOffset(int a, short *b, short *c);
void Mess_Message(char *a, char *b, int c, short d, short e);

void FUN_8006eb18(int **p) {
	short x, y;

	Panel_GetViewportMessOffset(DAT_800d173c * 2 + *(unsigned short *)((char *)*p + 2348),
	                                    &x, &y);

	if (*p == DAT_800d17c8)
		Mess_Message(DAT_800a5e94[0], DAT_800a6070, 0, x, y);
	else
		Mess_Message(DAT_800a5e98[0], DAT_800a6070, 0, x, y);
}
