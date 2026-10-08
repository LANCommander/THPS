/* Shake__7CCameraRC7CVector10EShakeType (0x800789d8) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short x, y, z;
} SV;

typedef struct {
	signed char x, y, z;
} BV;

typedef struct {
	char _0[0x572];
	SV a;
	BV b;
	char _57b;
	SV c;
} CCamera;

SV DAT_800d243c, DAT_800d2434, DAT_800d242c, DAT_800d241c;
BV DAT_800d2424;

extern void *DAT_800d1998 __attribute__((section(".data")));
extern void *DAT_800d19b0 __attribute__((section(".data")));
void SendShake(const V *, void *, int);

void CCamera_Shake(CCamera *t, const V *v, int type) {
	switch (type) {
		case 0:
			t->a = DAT_800d243c;
			goto tail;
		case 1:
			t->a = DAT_800d2434;
			goto tail;
		case 2:
			t->a = DAT_800d242c;
		tail:
			t->b = DAT_800d2424;
			t->c = DAT_800d241c;
			break;
	}

	SendShake(v, DAT_800d1998, type);
	SendShake(v, DAT_800d19b0, type);
}
