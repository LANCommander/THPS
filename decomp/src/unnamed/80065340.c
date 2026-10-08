/* _._14VerticalDialog (0x80065340) */
extern char DAT_800a2140[];

int BASEF(char *p, int a);
void __dl__6CClassPv(void *p);

void FUN_80065340(char *p, int f) {
	*(char **)p = DAT_800a2140;
	BASEF(p, 0);

	if (f & 1)
		__dl__6CClassPv(p);
}
