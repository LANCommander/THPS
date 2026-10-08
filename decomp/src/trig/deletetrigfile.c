/* Trig_DeleteTrigFile__Fv (0x80044ea8) */
void *DAT_800d19e0;
int DAT_800d19d8, DAT_800d19dc;

void FUN_8004d5d0(void *p);

void Trig_DeleteTrigFile(void) {
	if (DAT_800d19e0) {
		FUN_8004d5d0(DAT_800d19e0);

		DAT_800d19e0 = 0;
	}

	DAT_800d19d8 = 0;
	DAT_800d19dc = 0;
}
