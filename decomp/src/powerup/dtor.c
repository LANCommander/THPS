/* _._8CPowerUp (0x8001fe14) */
extern char DAT_8009f0f8[];

void *DAT_800d1618;

void DeleteFrom__5CBodyPP5CBody(char *, void *);
void DeleteStuff__8CPowerUp(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__8CPowerUp(char *t, int f) {
	*(char **)(t + 0x48) = DAT_8009f0f8;
	DeleteFrom__5CBodyPP5CBody(t, &DAT_800d1618);
	DeleteStuff__8CPowerUp(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
