/* _._5CTape (0x80073228) */
extern char DAT_800a3060[];

extern void *DAT_800d1618 __attribute__((section(".data")));
void DeleteFrom__5CBodyPP5CBody(char *, void *);
void DeleteStuff__5CTape(char *);
void FUN_80043860(char *, int);
void __dl__5CItemPv(char *);

void __dt__5CTape(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a3060;
	DeleteFrom__5CBodyPP5CBody(t, &DAT_800d1618);
	DeleteStuff__5CTape(t);
	FUN_80043860(t, 0);

	if (f & 1)
		__dl__5CItemPv(t);
}
