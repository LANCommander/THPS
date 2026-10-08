/* SaveReturnState__Fv (0x80012774) */
#include "names.h"
int DAT_800d1148;
int DAT_800d21e0;

int InCompetition(void);
int Competition_IsOver(void);

int SaveReturnState(void) {
	if (DAT_800d1148 == 0) {
		if (InCompetition() && !Competition_IsOver())
			return 25;

		return 15;
	}

	return DAT_800d21e0;
}
