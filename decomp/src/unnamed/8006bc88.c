/* FUN_8006bc88 (0x8006bc88) */
/* Builds the object's rotation matrix and runs FUN_8006b6c0 against the skater and its partner
   (+0x1c), unless a replay/video mode 2 is active on either player. */
#include <sys/types.h>
#include <libgte.h>

typedef struct {
	int VideoMode;
	char pad[0xc0 - 4];
} SVideoInfo;

typedef struct {
	char pad[16];
	char *p10;
} SModelInfo;

typedef struct {
	char pad[16];
	SModelInfo *pInfo;
	char q[64 - 20];
} SType;

extern SVideoInfo DAT_800bf318;
extern SVideoInfo DAT_800bf3d8;
extern SType DAT_800bf7a8[];
extern char *DAT_800d19a4;

void FUN_8006b6c0(char *, char *, MATRIX *, char *);

void FUN_8006bc88(char *p) {
	MATRIX m;
	SModelInfo *info;
	char *s1, *s2, *x;

	if (DAT_800bf318.VideoMode == 2 || DAT_800bf3d8.VideoMode == 2)
		return;

	info = DAT_800bf7a8[(unsigned char)p[27]].pInfo;
	s1 = DAT_800d19a4;
	s2 = *(char **)(s1 + 28);
	x = info->p10 + 12;
	RotMatrix((SVECTOR *)(p + 356), &m);
	FUN_8006b6c0(p, s1, &m, x);

	if (s2)
		FUN_8006b6c0(p, s2, &m, x);
}
