/* _card_event_x__Fv (0x80014fd4) */
int DAT_800d13ac, DAT_800d13b0, DAT_800d13b4, DAT_800d13b8;

int FUN_8008eb08(int);

int _card_event_x__Fv(void) {
	for (;;) {
		if (FUN_8008eb08(DAT_800d13ac) == 1)
			return 1;

		if (FUN_8008eb08(DAT_800d13b0) == 1)
			return 2;

		if (FUN_8008eb08(DAT_800d13b4) == 1)
			return 3;

		if (FUN_8008eb08(DAT_800d13b8) == 1)
			return 4;
	}
}
