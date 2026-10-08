/* MyVSync__Fv (0x80047870) */
#include "names.h"
int DAT_800d1a20;
int DAT_800d1a24, DAT_800d1a30;

extern int DAT_800d140c, DAT_800d16fc;

int Db_Vblank(void);
void SFX_ProcessingPerFrame(void);
void Utils_VblankProcessing(void);

void MyVSync(void) {
	DAT_800d1a20++;
	Db_Vblank();
	SFX_ProcessingPerFrame();

	if (!DAT_800d140c && !DAT_800d16fc)
		DAT_800d1a24++;

	if (DAT_800d1a30)
		Utils_VblankProcessing();
}
