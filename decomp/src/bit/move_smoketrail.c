/* Move__11CSmokeTrail (0x8002a49c) */
#include "names.h"
int CFT4Bit_Fade(void *, int);
void CBit_Die(char *);

void CSmokeTrail_Move(char *t) {
	int i;
	int dead = 1;

	if (*(int *)(t + 0x60)) {
		for (i = 0; i < *(int *)(t + 0x48); i++)
			if (!CFT4Bit_Fade((*(void ***)(t + 0x5c))[i], 0))
				dead = 0;

		if (dead)
			CBit_Die(t);
	}
}
