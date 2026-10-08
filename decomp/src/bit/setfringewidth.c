/* SetFringeWidth__5CGlowUiUi (0x80028fd4) */
#include "names.h"
typedef struct {
	int a, b;
} E;

void CGlow_SetFringeWidth(char *t, unsigned a, unsigned w) {
	unsigned i;
	E *p = *(E **)(t + 0x4c) + a * *(unsigned *)(t + 0x50);

	for (i = 0; i < *(unsigned *)(t + 0x50); i++)
		p[i].a = w;
}
