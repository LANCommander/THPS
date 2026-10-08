/* RemoveTextureEntry__FP7Texture (0x8006efb8) */
struct N {
	char pad[16];
	unsigned f;
	unsigned id;
	char pad2[8];
	struct N *a;
	struct N *b;
};

extern struct N *DAT_800c01a8[];

void Mem_Delete__FPv(struct N *p);

void RemoveTextureEntry__FP7Texture(struct N *p) {
	struct N **s;

	if (p->a)
		p->a->b = p->b;

	if (p->b)
		p->b->a = p->a;

	s = &DAT_800c01a8[p->id & 511];

	if (p == *s)
		*s = p->a;

	Mem_Delete__FPv(p);
}
