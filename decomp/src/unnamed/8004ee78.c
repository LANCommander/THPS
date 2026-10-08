/* FUN_8004ee78 (0x8004ee78) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
	char pad[12];
	struct O *next;
	char pad2[16];
	struct O *next2;
};

struct O *DAT_800d1b70;

void FUN_8004ee78(void) {
	struct O *p = DAT_800d1b70;
	struct O *n;

	while (p) {
		n = p->next;

		if (p)
			p->vt->fn((char *)p + p->vt->off, 3);

		p = n;
	}
}
