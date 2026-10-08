/* SaveReturnState__Fv (0x80012774) */
int DAT_800d1148;
int DAT_800d21e0;

int FUN_800164e4(void);
int FUN_8007409c(void);

int SaveReturnState(void) {
	if (DAT_800d1148 == 0) {
		if (FUN_800164e4() && !FUN_8007409c())
			return 25;

		return 15;
	}

	return DAT_800d21e0;
}
