/* _._6CSuper (0x80043d5c) */
extern char DAT_800a0574[];

void Mem_Delete__FPv(void *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__6CSuper(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a0574;

	if (*(void **)(t + 0x184))
		Mem_Delete__FPv(*(void **)(t + 0x184));

	if (*(void **)(t + 0x188))
		Mem_Delete__FPv(*(void **)(t + 0x188));

	if (*(void **)(t + 0x13c))
		Mem_Delete__FPv(*(void **)(t + 0x13c));

	if (*(void **)(t + 0x138))
		Mem_Delete__FPv(*(void **)(t + 0x138));

	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
