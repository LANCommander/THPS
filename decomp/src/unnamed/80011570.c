/* FUN_80011570 (0x80011570) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

struct E {
	struct O *p;
	int pad[3];
	int x;
};

int DAT_800d1118;

extern struct E DAT_800a4434[];

void FUN_80011570(void) {
	int i;

	for (i = 0; i < DAT_800d1118; i++) {
		struct O *o = DAT_800a4434[i].p;

		if (o)
			o->vt->fn((char *)o + o->vt->off, 3);

		DAT_800a4434[i].x = 0;
	}

	DAT_800d1118 = 0;
}
