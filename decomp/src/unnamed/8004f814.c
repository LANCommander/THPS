/* _._5CRail (0x8004f814) flags=-fstructure-noalias */
struct L {
	char *vt;
	char pad[28];
	struct L *prev;
	struct L *next;
};

struct L *DAT_800d1b94;

extern char DAT_800a1340[];
extern char DAT_800a1350[];

void __dl__6CClassPv(void *p);

void FUN_8004f814(struct L *p, int f) {
	struct L *h = DAT_800d1b94;

	p->vt = DAT_800a1340;

	if (h == p)
		DAT_800d1b94 = p->next;

	if (p->prev)
		p->prev->next = p->next;

	if (p->next)
		p->next->prev = p->prev;

	p->vt = DAT_800a1350;

	if (f & 1)
		__dl__6CClassPv(p);
}
