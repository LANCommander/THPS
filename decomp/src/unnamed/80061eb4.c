/* FUN_80061eb4 (0x80061eb4) */
int DAT_800d1d98;
int OT_entry;

void FUN_80061eb4(int a) {
	if (DAT_800d1d98 != a) {
		if (a == 0)
			OT_entry -= 4096;
		else
			OT_entry += 4096;

		DAT_800d1d98 = a;
	}
}
