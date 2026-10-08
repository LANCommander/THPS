/* FUN_80043584 (0x80043584) */
extern char DAT_800a05f4[];

void __dl__5CItemPv(void *p);

void FUN_80043584(char *p, int f) {
	*(char **)(p + 72) = DAT_800a05f4;

	if (f & 1)
		__dl__5CItemPv(p);
}
