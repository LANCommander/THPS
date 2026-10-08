/* InitItem__6CBrucePc (0x80042988) */
typedef struct {
	char p[20];
} H;

extern H DAT_800a814c[] __attribute__((section(".data")));
void InitItem__5CItemPc(char *, char *);
void M3dUtils_ReadHooksPacket__FP6CSuperPv(char *, void *);

void InitItem__6CBrucePc(char *t, char *name) {
	InitItem__5CItemPc(t, name);
	M3dUtils_ReadHooksPacket__FP6CSuperPv(t, &DAT_800a814c[*(int *)(t + 0x2e8)]);
}
