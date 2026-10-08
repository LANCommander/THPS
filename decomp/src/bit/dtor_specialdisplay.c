/* _._15CSpecialDisplay (0x80027f04) */
extern char DAT_8009f890[];

void *DAT_800d18f0;

void DeleteFrom__4CBitPv(char *, void *);
void FUN_80027e80(char *, int);
void FUN_80027d70(char *);

void __dt__15CSpecialDisplay(char *t, int f) {
	*(char **)(t + 0x44) = DAT_8009f890;
	DeleteFrom__4CBitPv(t, &DAT_800d18f0);
	FUN_80027e80(t, 0);

	if (f & 1)
		FUN_80027d70(t);
}
