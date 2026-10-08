/* Panel_Letter__Fi (0x8006e24c) */
typedef struct {
	char pad[0xdec];
	int l[5];
} CBruce;

int DAT_800d1e64;

extern CBruce *DAT_800d19a4;

void FUN_8006e2fc(int);

int Panel_Letter(int n) {
	DAT_800d1e64 = 40;

	if ((unsigned)n < 5)
		DAT_800d19a4->l[n] = 1;

	if (DAT_800d19a4->l[0] == 1 && DAT_800d19a4->l[1] == 1 && DAT_800d19a4->l[2] == 1 &&
	    DAT_800d19a4->l[3] == 1 && DAT_800d19a4->l[4] == 1) {
		FUN_8006e2fc(2);
		return 1;
	}

	return 0;
}
