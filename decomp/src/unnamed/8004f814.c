/* _._5CRail (0x8004f814) flags=-fstructure-noalias */
struct L {
	char *vt;
	char pad[28];
	struct L *prev;
	struct L *next;
};

struct L *RailList;

extern char __vt_5CRail[];
extern char DAT_800a1350[];

void __dl__6CClassPv(void *p);

void FUN_8004f814(struct L *p, int f) {
	struct L *h = RailList;

	p->vt = __vt_5CRail;

	if (h == p)
		RailList = p->next;

	if (p->prev)
		p->prev->next = p->next;

	if (p->next)
		p->next->prev = p->prev;

	p->vt = DAT_800a1350;

	if (f & 1)
		__dl__6CClassPv(p);
}
