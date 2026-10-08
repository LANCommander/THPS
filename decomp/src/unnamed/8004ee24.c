/* FUN_8004ee24 (0x8004ee24) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

struct O *DAT_800d1b70;

void FUN_8004ee24(void) {
	struct O *p = DAT_800d1b70;
	struct O *q;

	if (p) {
		for (;;) {
			p->vt->fn((char *)p + p->vt->off, 3);

			q = DAT_800d1b70;

			if (!q)
				break;

			p = q;
		}
	}
}
