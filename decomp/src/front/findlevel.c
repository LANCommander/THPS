/* Front_FindLevel__FPc (0x8001cb30) */
typedef struct {
	char pad[20];
	char *name;
	char pad2[96];
} SLevel;

extern SLevel DAT_800a5398[];
extern int DAT_800d1764;

extern int Utils_CompareStrings(const char *, const char *, unsigned);

SLevel *Front_FindLevel(char *s) {
	SLevel *r = 0;
	int i = 0;

	while (*DAT_800a5398[i].name) {
		if (Utils_CompareStrings(DAT_800a5398[i].name, s, 0xffffffff)) {
			DAT_800d1764 = i;
			r = &DAT_800a5398[i];
			break;
		}

		if (++i >= 41)
			break;
	}

	return r;
}
