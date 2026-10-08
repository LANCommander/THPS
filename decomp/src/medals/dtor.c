/* _._6CMedal (0x80073c94) */
extern char DAT_800a314c[];

void DeleteStuff__6CMedal(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__6CMedal(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a314c;
	DeleteStuff__6CMedal(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
