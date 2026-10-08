/* setString__12VerticalMenuiPc (0x800646b0) */
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

char *FUN_8008e904(char *, char *);
void select__12VerticalMenui(VerticalMenu *, int);

void VerticalMenu_setString(VerticalMenu *m, int i, char *s) {
	FUN_8008e904(m->items[i].str, s);

	if (m->timer < 61 && i == m->cur)
		select__12VerticalMenui(m, i);
}
