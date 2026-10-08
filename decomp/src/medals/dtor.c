/* _._6CMedal (0x80073c94) */
extern char DAT_800a314c[];

void FUN_80073cf0(char *);
void FUN_80043860(char *, int);
void FUN_80043530(char *);

void __dt__6CMedal(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a314c;
	FUN_80073cf0(t);
	FUN_80043860(t, 0);

	if (f & 1)
		FUN_80043530(t);
}
