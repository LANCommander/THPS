/* EntryOff__5CMenuPCc (0x800168b4) */
#include "names.h"
int CMenu_FindEntry(char *, const char *);

void EntryOff(char *m, const char *s) {
	m += CMenu_FindEntry(m, s) * 0x18;
	m[0x25] = 0;
}
