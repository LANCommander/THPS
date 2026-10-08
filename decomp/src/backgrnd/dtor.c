/* _._11CBackground (0x8007821c) */
extern char DAT_800a3494[];

char *DAT_800d1fe4;
unsigned short DAT_800d1fe8;

void DeleteFrom__5CBodyPP5CBody(char *, void *);
void FUN_80043860(char *, int);
void FUN_80043530(char *);

void __dt__11CBackground(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a3494;
	DeleteFrom__5CBodyPP5CBody(t, &DAT_800d1fe4);

	DAT_800d1fe8--;
	FUN_80043860(t, 0);

	if (f & 1)
		FUN_80043530(t);
}
