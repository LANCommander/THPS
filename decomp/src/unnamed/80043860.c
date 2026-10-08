/* FUN_80043860 (0x80043860) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	char pad[68];
	struct VT *vt;
};

extern char DAT_800a05b4[];

void FUN_80043584(char *p, int a);
void __dl__5CItemPv(void *p);

void FUN_80043860(char *p, int f) {
	struct O *o = *(struct O **)(p + 208);

	*(char **)(p + 72) = DAT_800a05b4;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	FUN_80043584(p, 0);

	if (f & 1)
		__dl__5CItemPv(p);
}
