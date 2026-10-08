/* TrickMessage__10CPanelData (0x8006e7c0) */
#include "names.h"
void CPanelData_TrickMessageRefresh(int *p);

void CPanelData_TrickMessage(int *p) {
	if (p[226]) {
		p[83] = 1;
		p[84] = 0;
		CPanelData_TrickMessageRefresh(p);
	} else
		p[83] = 0;
}
