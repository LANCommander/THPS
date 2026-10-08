/* FUN_8004ab2c (0x8004ab2c) */
struct N {
	int a[1];
	short s;
	char c;
	char c2;
	int x;
	int y;
	int prev;
	int next;
};

struct N *DAT_800d1a80;
struct N *FUN_8004d068(int a, int b, int c);

struct N *FUN_8004ab2c(int p) {
	struct N *n = FUN_8004d068(24, 0, 1);
	struct N *h = DAT_800d1a80;

	n->next = 0;
	DAT_800d1a80 = n;
	n->prev = (int)h;

	if (h)
		h->next = (int)n;

	n->x = p;
	n->c = 0;
	n->s = 0;
	return n;
}
