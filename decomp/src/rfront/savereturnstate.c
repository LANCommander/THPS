/* SaveReturnState__Fv (0x80012774) */
int DAT_800d1148;
int DAT_800d21e0;

int InCompetition__Fv(void);
int Competition_IsOver__Fv(void);

int SaveReturnState(void) {
	if (DAT_800d1148 == 0) {
		if (InCompetition__Fv() && !Competition_IsOver__Fv())
			return 25;

		return 15;
	}

	return DAT_800d21e0;
}
