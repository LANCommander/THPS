/* FUN_8004ef80 (0x8004ef80) */
struct L {
	char *vt;
	int a, b, c;
	struct L *next;
};

struct L *DAT_800d1b70;

extern char DAT_800a1320[];
extern char DAT_800a1330[];

void FUN_80024238(void *p);

void FUN_8004ef80(struct L *p, int f) {
	struct L *prev = 0;
	struct L *c = DAT_800d1b70;

	p->vt = DAT_800a1320;

	while (c != p) {
		prev = c;
		c = c->next;
	}

	if (prev)
		prev->next = p->next;
	else
		DAT_800d1b70 = p->next;

	p->vt = DAT_800a1330;

	if (f & 1)
		FUN_80024238(p);
}
