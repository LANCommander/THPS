/* Font_Init__Fv (0x8004c14c) */
#include "names.h"
extern char DAT_800a1270[];
extern char DAT_800d1ae4[];

int FontAnim, BigFontAnim;

int Spool_FindAnim(char *);

void Font_Init(void) {
	FontAnim = Spool_FindAnim(DAT_800a1270);
	BigFontAnim = Spool_FindAnim(DAT_800d1ae4);
}
