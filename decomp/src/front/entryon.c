/* EntryOn__5CMenuPCc (0x80016878) */
#include "names.h"
int CMenu_FindEntry(char *, const char *);

void EntryOn(char *m, const char *s) {
	m += CMenu_FindEntry(m, s) * 0x18;
	m[0x25] = 1;
}
