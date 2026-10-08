/* __9VMenuItemi (0x80029d80) */
extern char DAT_8009f6d0[];

void __8MenuItemi(char *, int);

char *VMenuItem_ctor(char *this, int n) {
	__8MenuItemi(this, n);

	*(char **)(this + 0x44) = DAT_8009f6d0;
	return this;
}
