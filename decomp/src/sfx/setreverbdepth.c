/* SFX_SetReverbDepth__FUcUc (0x8004bb1c) */
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

extern void FUN_80093914(ATTR *);

void SFX_SetReverbDepth(unsigned char l, unsigned char r) {
	ATTR a;

	a.mask = 6;
	a.depth.left = l << 8;
	a.depth.right = r << 8;
	FUN_80093914(&a);
}
