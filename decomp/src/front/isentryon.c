/* IsEntryOn__5CMenuPCc (0x800168ec) */
int FindEntry__5CMenuPCc(char *, const char *);

int IsEntryOn(char *m, const char *s) {
	m += FindEntry__5CMenuPCc(m, s) * 0x18;
	return m[0x25] == 1;
}
