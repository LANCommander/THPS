/* SFX_SetReverbType__FUc (0x8004ba7c) */
typedef struct {
	short left, right;
} VOL;

typedef struct {
	long mask;
	long mode;
	VOL depth;
	long delay;
	long feedback;
} ATTR;

extern long FUN_80093914(ATTR *);
extern long FUN_80094ca4(long);
extern long FUN_80094c74(long, long);

int DAT_800d1ac4;

void SFX_SetReverbType(unsigned char t) {
	ATTR a;

	a.mask = 1;
	a.mode = t;

	if (FUN_80093914(&a) == -1)
		return;

	if (t == 0) {
		DAT_800d1ac4 = 0;
		FUN_80094c74(0, 0xffffff);
	} else if (FUN_80094ca4(1)) {
		DAT_800d1ac4 = 0xf0;
		FUN_80094c74(1, 0xffffff);
	} else
		FUN_80094c74(0, 0xffffff);
}
