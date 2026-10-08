/* Move__11CSimpleAnim (0x80029974) */
#include "names.h"
typedef struct {
	char p[0x59];
	unsigned char n;
	signed char f;
	char q[0x70 - 0x5b];
	int once;
	int end;
} B;

void CFT4Bit_IncFrame(B *);
void CBit_Die(B *);
void CFT4Bit_SetFrame(B *, int);

void CSimpleAnim_Move(B *t) {
	CFT4Bit_IncFrame(t);

	if (t->once) {
		if (t->f >= t->end)
			CBit_Die(t);
	} else if (t->f >= t->n) {
		if (t->end == -2)
			CFT4Bit_SetFrame(t, t->n - 1);
		else
			CFT4Bit_SetFrame(t, 0);
	}
}
