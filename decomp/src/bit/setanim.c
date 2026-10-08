/* SetAnim__7CFT4BitPc (0x80028100) */
char *Spool_FindAnim__FPc(char *);

void SetAnim__7CFT4BitPc(char *t, char *name) {
	char *p = Spool_FindAnim__FPc(name);
	char n;

	*(char **)(t + 0x50) = p;
	n = p[-4];
	t[0x5a] = 0;
	t[0x5b] = 0;
	*(char **)(t + 0x54) = p;
	t[0x59] = n;
}
