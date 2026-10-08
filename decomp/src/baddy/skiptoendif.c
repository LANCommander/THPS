/* SkipToEndif__6CBaddy (0x8003fbc4) */
#include "names.h"
void CBaddy_SkipToEndif(char *t) {
	int depth = 0;
	unsigned short op;

	do {
		op = **(unsigned short **)(t + 0x1b0);
		*(unsigned short **)(t + 0x1b0) += 1;

		if (op == 0x4120) {
			if (depth == 0)
				return;

			depth--;
		} else if ((unsigned)(op - 0x4112) < 5)
			depth++;
	} while (op != 0x4100);
}
