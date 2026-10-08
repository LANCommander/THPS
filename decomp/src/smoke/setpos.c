/* SetPos__9CSmokeJetRC7CVector (0x80015bd8) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	V pos;
	char pad[24];
} P;

V *Utils_GetVecFromMagDir(V *, int, void *);
V *__adv__7CVectorRCi(V *, int *);
V *__apl__7CVectorRC7CVector(V *, V *);

void CSmokeJet_SetPos(char *t, V *p) {
	V d, pos;
	int n;
	int i;

	Utils_GetVecFromMagDir(&d, *(int *)(t + 0x168), t + 0x162);

	n = 9;
	__adv__7CVectorRCi(&d, &n);

	pos = *p;

	for (i = 0; i < 10; i++) {
		(*(P **)(t + 0x68))[i].pos = pos;
		__apl__7CVectorRC7CVector(&pos, &d);
	}
}
