/* SetAnim__7CFT4BitPc (0x80028100) */
#include "names.h"
char *Spool_FindAnim(char *);

void CFT4Bit_SetAnim(char *t, char *name) {
	char *p = Spool_FindAnim(name);
	char n;

	*(char **)(t + 0x50) = p;
	n = p[-4];
	t[0x5a] = 0;
	t[0x5b] = 0;
	*(char **)(t + 0x54) = p;
	t[0x59] = n;
}
