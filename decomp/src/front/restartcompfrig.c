/* RestartCompFrig__Fv (0x8001a6a8) */
#include "names.h"
extern int DAT_800d1e28;
extern int DAT_800d19e4;
extern char DAT_8009e4dc[];

void Trig_SetRestart(char *);
void Trig_ExecuteRestart(void);

void RestartCompFrig(void) {
	if (DAT_800d1e28 == 8) {
		int s = DAT_800d19e4;

		Trig_SetRestart(DAT_8009e4dc);
		Trig_ExecuteRestart();

		DAT_800d19e4 = s;
	}
}
