/* InitItem__6CBrucePc (0x80042988) */
#include "names.h"
typedef struct {
	char p[20];
} H;

extern H SkaterHooks[] __attribute__((section(".data")));
void CItem_InitItem(char *, char *);
void M3dUtils_ReadHooksPacket(char *, void *);

void CBruce_InitItem(char *t, char *name) {
	CItem_InitItem(t, name);
	M3dUtils_ReadHooksPacket(t, &SkaterHooks[*(int *)(t + 0x2e8)]);
}
