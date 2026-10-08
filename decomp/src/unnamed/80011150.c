/* FUN_80011150 (0x80011150) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

struct O *DAT_800d21d0;
struct O *DAT_800d21d4;
struct O *pVertMenu;

void FUN_80011150(void) {
	struct O *o = DAT_800d21d0;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	o = DAT_800d21d4;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	o = pVertMenu;
	DAT_800d21d4 = 0;
	DAT_800d21d0 = 0;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	pVertMenu = 0;
}
