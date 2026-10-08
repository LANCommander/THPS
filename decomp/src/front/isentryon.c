/* IsEntryOn__5CMenuPCc (0x800168ec) */
#include "names.h"
int CMenu_FindEntry(char *, const char *);

int IsEntryOn(char *m, const char *s) {
	m += CMenu_FindEntry(m, s) * 0x18;
	return m[0x25] == 1;
}
