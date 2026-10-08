/* GetVariable__9CPlatformUs (0x8003f624) */
#include "names.h"
int CBaddy_GetVariable(char *, unsigned short);

int CPlatform_GetVariable(char *t, unsigned short v) {
	if (v == 0x2200)
		return *(short *)(t + 0x240);

	return CBaddy_GetVariable(t, v);
}
