/* _._14VerticalDialog (0x80065340) */
extern char __vt_14VerticalDialog[];

int BASEF(char *p, int a);
void __dl__6CClassPv(void *p);

void FUN_80065340(char *p, int f) {
	*(char **)p = __vt_14VerticalDialog;
	BASEF(p, 0);

	if (f & 1)
		__dl__6CClassPv(p);
}
