/* Card_SetSelectedFile__FPc (0x80014218) */
#include "names.h"
extern char CARD_FNAME[];
extern char CARD_VNAME[];

void Card_SetSelectedFile(char *p) {
	CARD_FNAME[22] = p[17];
	CARD_FNAME[23] = p[18];
	CARD_VNAME[22] = p[17];
	CARD_VNAME[23] = p[18];
}
