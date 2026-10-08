/* _card_event__Fv (0x80014ee8) */
int DAT_800d139c, DAT_800d13a0, DAT_800d13a4, DAT_800d13a8, DAT_800d13bc;

int FUN_8008eb08(int);

int _card_event__Fv(void) {
	int r = FUN_8008eb08(DAT_800d139c) == 1;

	if (FUN_8008eb08(DAT_800d13a0) == 1)
		r = 2;

	if (FUN_8008eb08(DAT_800d13a4) == 1)
		r = 3;

	if (FUN_8008eb08(DAT_800d13a8) == 1)
		r = 4;

	if (DAT_800d13bc++ >= 120)
		r = 2;

	return r;
}
