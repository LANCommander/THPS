/* OutOfBounds__10CPanelData (0x8006eba4) */
#include "names.h"
int Redbook_Rnd(int a);
void FallingTextEffect_init(char *p);

void CPanelData_OutOfBounds(char *p) {
	*(int *)(p + 428) = Redbook_Rnd(4) + 1;
	FallingTextEffect_init(p + 432);
}
