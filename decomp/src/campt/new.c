/* CamPt_New__Fi (0x8004e21c) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

extern short DAT_800be344[];

int DAT_800d1b6c;

void Trig_GetPosition(V *v, int n);

void CamPt_New(int n) {
	V v;

	Trig_GetPosition(&v, n);

	DAT_800be344[DAT_800d1b6c++] = n;
}
