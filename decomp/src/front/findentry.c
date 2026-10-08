/* FindEntry__5CMenuPCc (0x80016770) */
typedef struct {
	const char *name;
	int pad[5];
} Entry;

typedef struct {
	char pad[9];
	unsigned char n;
	char pad2[14];
	Entry e[15];
} CMenu;

extern int Utils_CompareStrings(const char *, const char *, unsigned);

int FindEntry(CMenu *m, const char *s) {
	int i;

	for (i = 0; i < m->n; i++)
		if (Utils_CompareStrings(s, m->e[i].name, 0xffffffff))
			return i;

	return 0;
}
