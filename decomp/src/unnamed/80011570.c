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

int FreeSprite;

extern struct E BGCache[];

void FUN_80011570(void) {
	int i;

	for (i = 0; i < FreeSprite; i++) {
		struct O *o = BGCache[i].p;

		if (o)
			o->vt->fn((char *)o + o->vt->off, 3);

		BGCache[i].x = 0;
	}

	FreeSprite = 0;
}
