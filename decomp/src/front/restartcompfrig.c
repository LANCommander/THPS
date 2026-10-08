/* RestartCompFrig__Fv (0x8001a6a8) */
#include "names.h"
extern int GLevel;
extern int RestartNode;
extern char DAT_8009e4dc[];

void Trig_SetRestart(char *);
void Trig_ExecuteRestart(void);

void RestartCompFrig(void) {
	if (GLevel == 8) {
		int s = RestartNode;

		Trig_SetRestart(DAT_8009e4dc);
		Trig_ExecuteRestart();

		RestartNode = s;
	}
}
