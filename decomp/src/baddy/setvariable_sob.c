/* SetVariable__16CScriptOnlyBaddyUs (0x8004167c) */
#include "names.h"
void CBaddy_SetVariable(char *, unsigned short);

void CScriptOnlyBaddy_SetVariable(char *t, unsigned short v) {
	CBaddy_SetVariable(t, v);
}
