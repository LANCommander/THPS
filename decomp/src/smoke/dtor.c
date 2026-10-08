/* _._9CSmokeJet (0x80015b84) */
#include "names.h"
extern char DAT_8009e2c0[];

void FUN_8002e290(char *, int);
void __dl__4CBitPv(char *);

void __dt__9CSmokeJet(char *t, int f) {
	*(char **)(t + 0x44) = DAT_8009e2c0;
	FUN_8002e290(t, 0);

	if (f & 1)
		__dl__4CBitPv(t);
}
