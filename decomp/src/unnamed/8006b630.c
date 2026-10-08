/* FUN_8006b630 (0x8006b630) */
extern char DAT_800a233c[];
extern char DAT_800d1998[];

void DeleteFrom__5CBodyPP5CBody(char *p, char *q);
int BASEF(char *p, int a);
void FUN_80043530(void *p);

void FUN_8006b630(char *p, int f) {
	*(char **)(p + 72) = DAT_800a233c;
	DeleteFrom__5CBodyPP5CBody(p, DAT_800d1998);
	BASEF(p, 0);

	if (f & 1)
		FUN_80043530(p);
}
