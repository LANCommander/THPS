/* SendSignalToLinks__FPUs (0x80045d70) */
#include "names.h"
extern void *DAT_800d1998, *DAT_800d19b0;

short **DAT_800d19e8;

void SendSignalToNode(void *b, int node);

void SendSignalToLinks(unsigned short *p) {
	int i, n = p[0];
	unsigned short *q = p + 1;

	for (i = 0; i < n; i++) {
		int node = *q;
		short t = *DAT_800d19e8[node];

		if (t == 1 || t == 7) {
			SendSignalToNode(DAT_800d1998, node);
			SendSignalToNode(DAT_800d19b0, node);
		}

		q++;
	}
}
