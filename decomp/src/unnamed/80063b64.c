/* _._6Sprite (0x80063b64) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

struct O {
	struct VT *vt;
};

extern char DAT_800a2190[];
extern char DAT_800a21b0[];

void __dl__6CClassPv(void *p);

void FUN_80063b64(char **p, int f) {
	struct O *o = (struct O *)p[5];

	*p = DAT_800a2190;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);

	*p = DAT_800a21b0;

	if (f & 1)
		__dl__6CClassPv(p);
}
