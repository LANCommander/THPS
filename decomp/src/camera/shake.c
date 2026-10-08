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

SV BigShakeAmp, MediumShakeAmp, SmallShakeAmp, LandShakeSpeed;
BV LandShakeDecay;

extern void *BaddyList __attribute__((section(".data")));
extern void *EnvironmentalObjectList __attribute__((section(".data")));
void SendShake(const V *, void *, int);

void CCamera_Shake(CCamera *t, const V *v, int type) {
	switch (type) {
		case 0:
			t->a = BigShakeAmp;
			goto tail;
		case 1:
			t->a = MediumShakeAmp;
			goto tail;
		case 2:
			t->a = SmallShakeAmp;
		tail:
			t->b = LandShakeDecay;
			t->c = LandShakeSpeed;
			break;
	}

	SendShake(v, BaddyList, type);
	SendShake(v, EnvironmentalObjectList, type);
}
