/* SyncToGoodState__Fv (0x80014424) */
#include "names.h"
int CardStatusMode, CardLoadFlag, CardStatusTemp, CardStatus;

void FUN_8008eebc(int);
int Card_CheckStatus(int, int);

int SyncToGoodState(void) {
	int n = 200;

	CardStatusMode = 0;
	CardLoadFlag = 0;

	for (;;) {
		FUN_8008eebc(0);
		Card_CheckStatus(0, 0);

		if (CardLoadFlag == 1)
			break;

		if (--n < 0) {
			CardStatusTemp = 0;
			CardStatus = 0;
			return 1;
		}
	}

	CardStatusTemp = 1;
	CardStatus = 1;
	return 0;
}
