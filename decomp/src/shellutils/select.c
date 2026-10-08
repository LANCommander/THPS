/* select__12VerticalMenui (0x80065120) */
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

void VerticalMenu_select(VerticalMenu *m, int i) {
	if (!m->items[i].disabled) {
		m->prev = m->cur;
		m->cur = i;

		if (m->timer > 60)
			m->timer = 62;
		else
			m->timer = 64;
	}
}
