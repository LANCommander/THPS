/* FUN_8004f318 (0x8004f318) */
typedef struct T {
	char *vt;
	unsigned int mChecksum;
	char pad[8];
	struct T *mpNext;
} T;

T *DAT_800d1b70;

unsigned int FUN_8006ef00(void);

int FUN_8004f318(void) {
	unsigned int c = FUN_8006ef00();
	T *p;

	for (p = DAT_800d1b70; p; p = p->mpNext)
		if (p->mChecksum == c)
			break;

	return p ? 2 : 1;
}
