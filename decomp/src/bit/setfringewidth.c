/* SetFringeWidth__5CGlowUiUi (0x80028fd4) */
typedef struct {
	int a, b;
} E;

void SetFringeWidth__5CGlowUiUi(char *t, unsigned a, unsigned w) {
	unsigned i;
	E *p = *(E **)(t + 0x4c) + a * *(unsigned *)(t + 0x50);

	for (i = 0; i < *(unsigned *)(t + 0x50); i++)
		p[i].a = w;
}
