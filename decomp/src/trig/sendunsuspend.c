/* SendUnSuspend__Fi (0x80045e98) */
#include "names.h"
extern char *DAT_800d19b4;

void CBody_UnSuspend(char *b);

void SendUnSuspend(int node) {
	char *b;

	for (b = DAT_800d19b4; b; b = *(char **)(b + 0x1c))
		if (*(unsigned short *)(b + 0xe2) == node)
			CBody_UnSuspend(b);
}
