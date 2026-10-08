/* FUN_80043af4 (0x80043af4) */
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

void FUN_80043af4(char *p) {
	struct O *o;

	*(unsigned short *)(p + 82) &= 0xfff7;
	o = *(struct O **)(p + 208);

	if (o) {
		o->vt->fn((char *)o + o->vt->off, 3);

		*(int *)(p + 208) = 0;
	}
}
