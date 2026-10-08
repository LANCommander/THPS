/* _._5CTape (0x80073228) */
extern char DAT_800a3060[];

extern void *DAT_800d1618 __attribute__((section(".data")));
void DeleteFrom__5CBodyPP5CBody(char *, void *);
void FUN_800732e4(char *);
void FUN_80043860(char *, int);
void FUN_80043530(char *);

void __dt__5CTape(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a3060;
	DeleteFrom__5CBodyPP5CBody(t, &DAT_800d1618);
	FUN_800732e4(t);
	FUN_80043860(t, 0);

	if (f & 1)
		FUN_80043530(t);
}
