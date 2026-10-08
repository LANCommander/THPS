/* FUN_8004f5d0 (0x8004f5d0) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

struct O *DAT_800d1b94;

void FUN_8004f5d0(void) {
	struct O *p = DAT_800d1b94;
	struct O *q;

	if (p) {
		for (;;) {
			p->vt->fn((char *)p + p->vt->off, 3);

			q = DAT_800d1b94;

			if (!q)
				break;

			p = q;
		}
	}

	DAT_800d1b94 = 0;
}
