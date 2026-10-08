/* _._9CPlatform (0x8003d7a0) */
extern char DAT_800a013c[];

extern void *DAT_800d19b0 __attribute__((section(".data")));
void DeleteFrom__5CBodyPP5CBody(char *, void *);
void SFX_Stop__FUi(unsigned);
void __dt__6CBaddy(char *, int);
void FUN_80043530(char *);

void __dt__9CPlatform(char *t, int f) {
	*(char **)(t + 0x48) = DAT_800a013c;
	DeleteFrom__5CBodyPP5CBody(t, &DAT_800d19b0);

	if (*(unsigned *)(t + 0x244)) {
		SFX_Stop__FUi(*(unsigned *)(t + 0x244));

		*(unsigned *)(t + 0x244) = 0;
	}

	__dt__6CBaddy(t, 0);

	if (f & 1)
		FUN_80043530(t);
}
