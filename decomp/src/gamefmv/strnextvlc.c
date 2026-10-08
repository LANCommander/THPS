/* strNextVlc__Fi (0x80023edc) */
int DAT_800d1640;
int DAT_800d168c[2];

int strNext__Fv(void);
void FUN_800224e4(int, int);
void FUN_8009144c(int);

int strNextVlc(int f) {
	int s = strNext__Fv();

	if (!s)
		return 0;

	if (f)
		FUN_800224e4(s, DAT_800d168c[DAT_800d1640]);

	FUN_8009144c(s);
	return f;
}
