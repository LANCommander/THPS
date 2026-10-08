/* ResetTrickBuffers__6CBruce (0x8002fe50) */
#include "names.h"
extern int XFrames;

void CBruce_ResetTrickBuffers(int *p) {
	int t = XFrames - p[157];

	p[201] = 0;
	p[220] = 0;
	p[219] = 0;
	p[232] = 0;
	p[222] = 0;

	if (t > 8) {
		p[160] = 0;
		p[159] = 0;
		p[157] = 0;
	}

	p[153] = 0;
	p[152] = 0;
	p[156] = 0;
	p[155] = 0;
}
