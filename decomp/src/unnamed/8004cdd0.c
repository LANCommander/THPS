/* FUN_8004cdd0 (0x8004cdd0) */
int DAT_800d1b14;
int DAT_800d1afc;

void FUN_8004cc18(void);
void FUN_8005dcc4(void);

void FUN_8004cdd0(void) {
	if (DAT_800d1b14) {
		DAT_800d1afc = 0;
		DAT_800d1b14 = 0;
		return;
	}

	while (DAT_800d1afc) {
		FUN_8004cc18();
		FUN_8005dcc4();
	}

	FUN_8004cc18();
}
