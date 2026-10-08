/* FUN_80025400 (0x80025400) */
extern int DAT_800a7214[];
extern int DAT_800d1a24;

int DAT_800d1844;

void FUN_80025400(void) {
	int i;

	for (i = 0; i < 3; i++)
		DAT_800a7214[i] = 2;

	DAT_800d1844 = DAT_800d1a24 - 2;
}
