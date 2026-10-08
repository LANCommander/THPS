/* M3dUtils_ReadHooksPacket__FP6CSuperPv (0x8008123c) */
struct S {
	char a[0x20];
	int field;
	char b[0x1c];
};

extern struct S DAT_800bf7a8[];

typedef struct {
	char _0[0x1b];
	unsigned char idx;
} CSuper;

void M3dUtils_ReadHooksPacket(CSuper *s, char *p) {
	p += 4;
	DAT_800bf7a8[s->idx].field = (int)p;
}
