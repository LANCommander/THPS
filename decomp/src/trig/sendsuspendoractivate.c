/* SendSuspendOrActivate__FPUsi (0x80045ef4) */
#include "names.h"
extern void *DAT_800d1998, *DAT_800d19b0;

short **DAT_800d19e8;

void SendSuspend(void **pp, int node);
void SendUnSuspend(int node);

void SendSuspendOrActivate(unsigned short *p, int mode) {
	int i, n = p[0];
	unsigned short *q = p + 1;

	for (i = 0; i < n; i++, q++) {
		int node = *q;
		short t = *DAT_800d19e8[node];

		if (t == 1 || t == 7) {
			if (mode == 5) {
				SendSuspend(&DAT_800d1998, node);
				SendSuspend(&DAT_800d19b0, node);
			} else {
				SendUnSuspend(node);
			}
		}
	}
}
