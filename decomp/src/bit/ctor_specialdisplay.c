/* __15CSpecialDisplay (0x80027ec4) */
extern char DAT_8009f890[];

void *DAT_800d18f0;

char *__4CBit(char *);
void AttachTo__4CBitPv(char *, void *);

char *__15CSpecialDisplay(char *t) {
	__4CBit(t);

	*(char **)(t + 0x44) = DAT_8009f890;
	AttachTo__4CBitPv(t, &DAT_800d18f0);
	return t;
}
