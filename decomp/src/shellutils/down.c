/* down__12VerticalMenu (0x80065230) */
#include "names.h"
typedef struct {
	int pad0;
	char str[0x34];
	int disabled;
	int pad1;
} Item;

typedef struct {
	char pad[16];
	int count;
	int prev;
	int cur;
	Item items[12];
	int timer;
} VerticalMenu;

extern char DAT_800c0a48[];

void Pad_ClearTriggers(void *);
void VerticalMenu_select(VerticalMenu *, int);

void VerticalMenu_down(VerticalMenu *m) {
	int n;

	if (m->timer > 60) {
		Pad_ClearTriggers(DAT_800c0a48);
		Pad_ClearTriggers(DAT_800c0a48 + 364);
	} else {
		n = m->cur + 1;

		if (n >= m->count)
			n = 0;

		while (n != m->cur && m->items[n].disabled) {
			n++;

			if (n >= m->count)
				n = 0;
		}

		VerticalMenu_select(m, n);
	}
}
