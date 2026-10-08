/* FUN_800620f0 (0x800620f0) */
extern char DAT_800a21a0[];
extern char DAT_800a21b0[];

void unpack__11SlicedImage(char *p);
void Pack_Unpack__Fss(short a, short b);
void FUN_8004d5d0(char *p);
void Free256Slot__FUs(unsigned short s);
void FUN_80024238(char *p);

void FUN_800620f0(char *p, int f) {
	*(char **)p = DAT_800a21a0;

	if (*(int *)(p + 44)) {
		unpack__11SlicedImage(p);
	} else if (*(short **)(p + 24)) {
		Pack_Unpack__Fss(**(short **)(p + 24), (*(short **)(p + 24))[1]);
		FUN_8004d5d0(*(char **)(p + 24));
	}

	if (*(int *)(p + 36) == 8)
		Free256Slot__FUs(*(unsigned short *)(p + 40));

	if (!*(int *)(p + 48))
		FUN_8004d5d0(*(char **)(p + 20));

	*(char **)p = DAT_800a21b0;

	if (f & 1)
		FUN_80024238(p);
}
