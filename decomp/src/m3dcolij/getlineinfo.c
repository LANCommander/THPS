/* M3dColij_GetLineInfo__FP9SLineInfo (0x800808b0) */
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>

typedef struct {
	char _0[0x68];
	char *obj;
	char _6c[0x78 - 0x6c];
	short v[3];
} SLineInfo;

extern char Tfm[];
extern SVECTOR *NearestHit_8[];

void FUN_8008b3d4(char *, char *);

int M3dColij_GetLineInfo(SLineInfo *li) {
	if (li->obj) {
		FUN_8008b3d4(li->obj + 16, Tfm);
		gte_SetRotMatrix(Tfm);
		gte_ldv0(NearestHit_8[0]);
		gte_rtv0();
		gte_stsv(li->v);
		return 1;
	}

	return 0;
}
