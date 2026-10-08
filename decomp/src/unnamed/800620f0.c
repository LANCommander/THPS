/* FUN_800620f0 (0x800620f0) */
extern char DAT_800a21a0[];
extern char DAT_800a21b0[];

void unpack__11SlicedImage(char *p);
void Pack_Unpack__Fss(short a, short b);
void Mem_Delete__FPv(char *p);
void Free256Slot__FUs(unsigned short s);
void __dl__6CClassPv(char *p);

void FUN_800620f0(char *p, int f) {
	*(char **)p = DAT_800a21a0;

	if (*(int *)(p + 44)) {
		unpack__11SlicedImage(p);
	} else if (*(short **)(p + 24)) {
		Pack_Unpack__Fss(**(short **)(p + 24), (*(short **)(p + 24))[1]);
		Mem_Delete__FPv(*(char **)(p + 24));
	}

	if (*(int *)(p + 36) == 8)
		Free256Slot__FUs(*(unsigned short *)(p + 40));

	if (!*(int *)(p + 48))
		Mem_Delete__FPv(*(char **)(p + 20));

	*(char **)p = DAT_800a21b0;

	if (f & 1)
		__dl__6CClassPv(p);
}
