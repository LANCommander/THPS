/* DequeueSoundCmd__FR13ESoundCmdTypeRi (0x80068e10) */
#include "names.h"
typedef struct {
	int type, val;
} SSoundCmd;

extern SSoundCmd DAT_800bf524[];

int DAT_800d1df4;

void DequeueSoundCmd(int *type, int *val) {
	*type = DAT_800bf524[DAT_800d1df4].type;
	*val = DAT_800bf524[DAT_800d1df4].val;
	DAT_800d1df4 = (DAT_800d1df4 + 1) % 30;
}
