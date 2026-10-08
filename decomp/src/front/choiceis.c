/* ChoiceIs__5CMenuPCc (0x8001692c) */
extern int Utils_CompareStrings(const char *, const char *, unsigned);

int ChoiceIs(unsigned char *m, const char *s) {
	m += m[6] * 0x18;
	return Utils_CompareStrings(s, *(const char **)(m + 0x18), 0xffffffff);
}
