/* Trig_RemoveDualBuffer__Fv (0x8004634c) */
void *DAT_800d1a0c;

void FUN_8004d5d0(void *p);

void Trig_RemoveDualBuffer(void) {
	if (DAT_800d1a0c)
		FUN_8004d5d0(DAT_800d1a0c);

	DAT_800d1a0c = 0;
}
