/* Trig_DeleteTrigFile__Fv (0x80044ea8) */
void *DAT_800d19e0;
int DAT_800d19d8, DAT_800d19dc;

void Mem_Delete__FPv(void *p);

void Trig_DeleteTrigFile(void) {
	if (DAT_800d19e0) {
		Mem_Delete__FPv(DAT_800d19e0);

		DAT_800d19e0 = 0;
	}

	DAT_800d19d8 = 0;
	DAT_800d19dc = 0;
}
